#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
//#include <sys/time.h>
#include <stdlib.h>
#include "philo.h"

void	finish_table(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->nbr_ph)
	{
		pthread_join(&(var->philos[i]), NULL);
		i++;
	}
	i = 0;
	while (i < var->nbr_ph)
	{
		pthread_mutex_destroy(&(var->forks[i]));
		i++;
	}
}

int	is_philo_died(t_philo *philo)
{
	long long	now;

	now = get_ms_time();
	if (now - philo->last_meal > philo->var->tm_die)
		return (1);
	return (0);
}

void	*check_death(void *arg)
{
	t_var	*var;
	int		i;
	t_philo	*philos;

	var = (t_var *)arg;
	get_start(var);
	i = 0;
	philos = var->philos;
	// check all the t_philo last meal and check death time.
	while (get_bool(&(var->start_mutex), &(var->start)))
	{
		while (i < var->nbr_ph)
		{
			if (is_philo_died(&philos[i]))
			{
				var->start = false;
				break;
			}
			i++;
		}
	}
	finish_table(var);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo *philo;
	t_var	*var;

	philo = (t_philo *)arg;
	var = philo->var;
	get_start(var);
	while (get_bool(&(var->start_mutex), &(var->start)))
	{
		eating(philo);
		sleep_think(philo);
	}
	// wait for lock: get_left_fork(); get_right_fork();
	// eat: last_meal = get_ms_time(); usleep(var->tm_eat);
	// unlock
	// sleep: sleep = get_ms_time(); usleep(var->tm_sleep);
	// thinking: start thinking until die or get forks again. 
	return (NULL);
}
