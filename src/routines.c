#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
//#include <sys/time.h>
#include <stdlib.h>
#include "philo.h"

static t_status	check_philo_status(t_philo *philo, int *all_full)
{
	long long	now;
	t_status	status;
	t_var		*var;

	now = get_ms_time();
	status = 0;
	var = philo->var;
	pthread_mutex_lock(&(philo->meal_mut));
	//printf("now %lldd - last meal %lld = %lld, tm die = %lld\n", now, philo->last_meal, now - philo->last_meal, philo->var->tm_die);
	if (now - philo->last_meal > philo->var->tm_die)
		status = DIED;
	else if (philo->full)
		(*all_full)++;
	pthread_mutex_unlock(&(philo->meal_mut));
	if (status == DIED)
	{
		if (!get_bool(&(var->stop_mutex), &(var->stop)))
		{
			set_bool(&(var->stop_mutex), &(var->stop), true);
			console_status(philo, DIED);
			set_bool(&(var->start_mutex), &(var->start), false);
		}
	}
	return (status);
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
		i = -1;
		all_full = 0;
		while (++i < var->nbr_ph)
			if (check_philo_status(&(var->philos[i]), &all_full) == DIED)
				break;
		//printf("var must eat = %d, all full = %d\n", var->must_eat, all_full);
		if (var->must_eat != -1 && all_full == var->nbr_ph)
		{
			set_bool(&(var->stop_mutex), &(var->stop), true);
			set_bool(&(var->start_mutex), &(var->start), false);
			break;
		}
		usleep(100);
	}
	return (NULL);
}

/**
 * If there is an odd amount of philos, let the even philo (the ones more) to wait 
 * then it will avoid the situation where one odd philo cannot take any forks;
 * because of its even neighbor always get a fork. usleep(1000) = 1ms
 */
void	eating(t_philo *philo)
{
	t_var	*var;

	var = philo->var;
	if (philo->id % 2 == 0)
		usleep(1000);
	pthread_mutex_lock(philo->first);
	console_status(philo, TAKE_FIRST_FORK);
	pthread_mutex_lock(philo->second);
	console_status(philo, TAKE_SECOND_FORK);
	pthread_mutex_lock(&(philo->meal_mut));
	philo->last_meal = get_ms_time();
	if (++philo->meals == var->must_eat && var->must_eat != -1)
		philo->full = true;
	pthread_mutex_unlock(&(philo->meal_mut));
	console_status(philo, EAT);
	usleep(var->tm_eat * 1000);
	pthread_mutex_unlock(philo->first);
	pthread_mutex_unlock(philo->second); 
}

void	sleep_think(t_philo *philo)
{
	t_var	*var;
	var = philo->var;
	console_status(philo, SLEEP);
	usleep(var->tm_sleep * 1000);
	console_status(philo, THINK);
}

void	*routine(void *arg)
{
	t_philo *philo;
	t_var	*var;

	philo = (t_philo *)arg;
	var = philo->var;
	get_start(var);
	if (philo->var->nbr_ph == 1)
	{
		console_status(philo, TAKE_FIRST_FORK);
		usleep(philo->var->tm_die * 1000);
		console_status(philo, DIED);
		return (NULL);
	}
	while (get_bool(&(var->start_mutex), &(var->start)))
	{
		if (get_bool(&(philo->meal_mut), &(philo->full)))
			break;
		eating(philo);
		sleep_think(philo);
	}
	return (NULL);
}
