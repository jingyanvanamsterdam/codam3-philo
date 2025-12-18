#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include "philo.h"

int	is_valid_input(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	init_var(int ac, char **av, t_var *var)
{
	var->nbr_philos = ft_atoi(av[1]);
	var->tm_die = ft_atoll(av[2]);
	var->tm_eat= ft_atoll(av[3]);
	var->tm_sleep = ft_atoll(av[4]);
	var->must_eat = 0;
	if (ac == 6)
		var->must_eat = ft_atoi(av[5]);
	var->threads = NULL;
	if (var->nbr_philos * var->tm_die * var->tm_eat * var->tm_sleep * var->must_eat < 0)
		return (0);
	return (1);
}

long long	get_ms_time(struct timeval *tv)
{
	if (gettimeofday(tv, NULL) == -1)
	{
		perror("gettimeofday failed.");
		return (-1);
	}
	return (tv->tv_sec * 1000LL + tv->tv_usec / 1000);
}

int	init_philo(pthread_t th, int i, t_var *var)
{
	t_philo	philo;

	philo.full = false;
	philo.id = i;
	philo.last_meal = 0;
	philo.left = create_fork();
	if (!philo.left)
		return (0);
	if (philo.right = get_prev_fork())
		return (0);
	philo.th_id = th;
	philo.var = var;
	return (1);
}

int	create_philos_threads(t_var *var)
{
	int	i;

	i = 0;
	var->threads = (pthread_t *) malloc(sizeof(pthread_t) * var->nbr_philos);
	if (!var->threads)
		return (perror("failed at malloc."), 0);
	while (i < var->nbr_philos)
	{
		if (pthread_create(var->threads + i, NULL, func, a) != 0)
		{
			perror("failed at creating thread.");
			return (0);
		}
		if (!init_philo(var->threads[i], i, var))
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char *av[])
{
	t_var		var;
	struct timeval tv;
	long long	time;
	

	if (ac < 5 || ac > 7)
		return (write(2, "input error", ft_strlen("input error")));
	if (!is_valid_input(av) || !init_var(ac, av, &var))
		return (write(2, "arg error", ft_strlen("arg error")));
	if (!create_philos_threads(&var))
	{
		// free var, destroy threads and forks. 
		return (write(2, "sys or malloc error", ft_strlen("sys error")));
	}

	time = get_ms_time(&tv);
	if (time == -1)
		return (write(2, "sys call error", ft_strlen("sys call error")));
	printf("time is %ld, %d, %lld\n", tv.tv_sec, tv.tv_usec, time);
	printf("philos = %d; to die = %lld ms; to eat = %lld ms; to sleep = %lld ms->\n", var.philos, var.tm_die, var.tm_eat, var.tm_sleep);


	/*
	time_die, time_eat, time_sleep, [number_of_times_each_philosopher_must_eat]
in miliseconds */
}