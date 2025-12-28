#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include "philo.h"

long long	get_ms_time(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		perror("gettimeofday failed.");
		return (-1);
	}
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}
/** 	
 * ./philo time_die, time_eat, time_sleep, [must_eat]
 * 
 * Wait for threads and cleanup resources. 
 * Without joining, main returns and the process exits which terminates all threads*/
int	main(int ac, char *av[])
{
	t_var		var;
	
	if (ac < 5 || ac > 7)
		return (ft_putstr_fd("input error", 2), 1);
	init_var(ac, av, &var);
	create_philos_threads(&var);
	ft_cleanup(&var, var.nbr_ph, var.nbr_ph);
	return (0);
}
