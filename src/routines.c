#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
//#include <sys/time.h>
#include <stdlib.h>
#include "philo.h"

int	is_philo_died(t_philo *philo)
{
	long long	now;

	now = get_ms_time();
	pthread_mutex_lock(&(philo->meal_mut));
	if (now - philo->last_meal > philo->var->tm_die)
		return (1);
	pthread_mutex_unlock(&(philo->meal_mut));
	return (0);
}

void	*check_death(void *arg)
{
	t_var	*var;
	int		i;
	int		all_full;

	var = (t_var *)arg;
	get_start(var);
	while (get_bool(&(var->start_mutex), &(var->start)))
	{
		i = 0;
		all_full = 0;
		while (i < var->nbr_ph)
		{
			if (is_philo_died(&(var->philos[i])))
			{
				set_bool(&var->start_mutex, &var->start, false);
				break;
			}
			if (var->philos[i++].full)
			{
				all_full++;
				//printf("all full++\n");
			}	
		}
		if (all_full == var->nbr_ph)
		{
			set_bool(&var->start_mutex, &var->start, false);
			printf("%d\n", all_full);
			break;
		}
		usleep(100);
	}
	//printf("finished loop in check death\n");
	//ft_cleanup(var, var->nbr_ph, var->nbr_ph);
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
		if (philo->full)
			break;
		eating(philo);
		sleep_think(philo);
	}
	// wait for lock: get_left_mutex(); get_right_mutex();
	// eat: last_meal = get_ms_time(); usleep(var->tm_eat);
	// unlock
	// sleep: sleep = get_ms_time(); usleep(var->tm_sleep);
	// thinking: start thinking until die or get forks again. 
	return (NULL);
}
