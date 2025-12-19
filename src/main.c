#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include "philo.h"
#include <errno.h>

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

void	prepare_forks(t_var *var)
{
	int	i;

	i = 0;
	var->forks = ft_calloc(var->nbr_ph, sizeof(t_fork));
	if (!var->forks)
		ft_failure_exit("malloc forks: ", var, 0, 0);
	while (i < var->nbr_ph)
	{
		if (pthread_mutex_init(var->forks + i, NULL) != 0)
			ft_failure_exit("creating forks: ", var, i, 0);
		i++;
	}
}

void	init_var(int ac, char **av, t_var *var)
{
	var->nbr_ph = ft_atoi(av[1]);
	var->tm_die = ft_atoll(av[2]);
	var->tm_eat= ft_atoll(av[3]);
	var->tm_sleep = ft_atoll(av[4]);
	var->must_eat = 0;
	if (ac == 6)
		var->must_eat = ft_atoi(av[5]);
	var->threads = NULL;
	if (pthread_mutex_init(&(var->start_mutex), NULL) != 0)
	{
		perror("create start mutex: ");
		exit(EXIT_FAILURE);
	}
	prepare_forks(var);
	if (pthread_create(&(var->check_die), NULL, check_routine, NULL) != 0)
		ft_failure_exit("create check death thread.", var, var->nbr_ph, 0);
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

void	init_philo(pthread_t th, int i, t_var *var)
{

	var->philos[i].full = false;
	var->philos[i].id = i;
	var->philos[i].last_meal = 0;
	var->philos[i].left = var->forks + i;
	var->philos[i].right = var->forks + (i + 1) % var->nbr_ph; 
	var->philos[i].th_id = th;
	var->philos[i].var = var;
	if (i == 0)
		printf("id = %d, philo.left = %p = %p prev right; right = %p, th adr = %p\n", i, var->philos[i].left, var->forks + (var->nbr_ph - 1), var->philos[i].right, &(var->philos[i].th_id));
	else 
		printf("id = %d, philo.left = %p = %p prev right; right = %p, th adr = %p\n", i, var->philos[i].left, var->forks + (i - 1), var->philos[i].right, &(var->philos[i].th_id));
}

void	*check_routine(void *arg)
{
	(void)arg;
	// start mutex wait for all the threads are created.
	// check all the t_philo last meal and check death time.
	return (NULL);
}

void	*routine(void *arg)
{
	(void)arg;
	// start mutex: wait for all the threads are created. 
	// wait for lock: get_left_fork(); get_right_fork();
	// eat: last_meal = get_ms_time(); usleep(var->tm_eat);
	// unlock
	// sleep: sleep = get_ms_time(); usleep(var->tm_sleep);
	// thinking: start thinking until die or get forks again. 
	return (NULL);
}

void	create_philos_threads(t_var *var)
{
	int	i;

	i = 0;
	var->threads = (pthread_t *)malloc(var->nbr_ph * sizeof(pthread_t));
	if (!var->threads)
		ft_failure_exit("malloc for threads: ", var, var->nbr_ph, 0);
	var->philos = (t_philo *)malloc(var->nbr_ph * sizeof(t_philo));
	if (!var->philos)
		ft_failure_exit("malloc for threads: ", var, var->nbr_ph, 0);
	while (i < var->nbr_ph)
	{
		if (pthread_create(var->threads + i, NULL, routine, NULL) != 0)
			ft_failure_exit("creating thread: ", var, var->nbr_ph, i);
		init_philo(var->threads[i], i, var);
		i++;
	}
}

void	ft_cleanup(t_var *var, int fork_i, int th_i)
{
	int i;

	i = 0;
	if (var->threads)
	{
		while (i < th_i)
		{
			if (pthread_join(var->threads[i], NULL) != 0)
				ft_putstr_fd("join threads fails", 2);
			i++;
		}
		free(var->threads);
	}
	if (var->forks)
	{
		i = 0;
		while (i < fork_i)
		{
			pthread_mutex_destroy(var->forks + i);
			i++;
		}
		free(var->forks);
	}
	pthread_mutex_destroy(&(var->start_mutex));
}

void	ft_failure_exit(char *mes, t_var *var, int fork_i, int th_i)
{
	int	i;

	i = 0;
	ft_putstr_fd(mes, 2);
	ft_cleanup(var, fork_i, th_i);
	exit(EXIT_FAILURE);
}

int	main(int ac, char *av[])
{
	t_var		var;
	struct timeval tv;
	long long	time;
	
	if (ac < 5 || ac > 7)
		return (write(2, "input error", ft_strlen("input error")));
	if (!is_valid_input(av))
		return (write(2, "arg error", ft_strlen("arg error")));
	init_var(ac, av, &var);
	create_philos_threads(&var);

	time = get_ms_time(&tv);
	if (time == -1)
		return (write(2, "sys call error", ft_strlen("sys call error")));
	printf("time is %ld, %d, %lld\n", tv.tv_sec, tv.tv_usec, time);
	printf("philos = %d; to die = %lld ms; to eat = %lld ms; to sleep = %lld ms->\n", var.nbr_ph, var.tm_die, var.tm_eat, var.tm_sleep);
	
	ft_cleanup(&var, var.nbr_ph, var.nbr_ph);
	//pthread_join(var->threads[i], NULL);
	/*
	time_die, time_eat, time_sleep, [number_of_times_each_philosopher_must_eat]
in miliseconds */
}