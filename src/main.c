#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
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

long long	get_ms_time(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		perror("gettimeofday failed.");
		return (-1);
	}
	//printf("time is %ld, %d, %lld\n", tv.tv_sec, tv.tv_usec);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

int	main(int ac, char *av[])
{
	t_var		var;
	long long	time;
	
	if (ac < 5 || ac > 7)
		return (ft_putstr_fd("input error", 2), 1);
	if (!is_valid_input(av))
		return (ft_putstr_fd("arg error", 2), 1);
	init_var(ac, av, &var);
	create_philos_threads(&var);

	time = get_ms_time();
	if (time == -1)
		return (write(2, "sys call error", ft_strlen("sys call error")));
	
	printf("philos = %d; to die = %lld ms; to eat = %lld ms; to sleep = %lld ms->\n", var.nbr_ph, var.tm_die, var.tm_eat, var.tm_sleep);
	
	ft_cleanup(&var, var.nbr_ph, var.nbr_ph);
	return (0);
	//pthread_join(var->threads[i], NULL);
	/*
	time_die, time_eat, time_sleep, [number_of_times_each_philosopher_must_eat]
in miliseconds */

}