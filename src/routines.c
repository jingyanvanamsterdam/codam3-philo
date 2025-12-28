#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
//#include <sys/time.h>
#include <stdlib.h>
#include "philo.h"

t_status	is_philo_died(t_philo *philo)
{
	long long	now;
	t_status	status;

	now = get_ms_time();
	status = 0;
	pthread_mutex_lock(&(philo->meal_mut));
	printf("now %lldd - last meal %lld = %lld, tm die = %lld\n", now, philo->last_meal, now - philo->last_meal, philo->var->tm_die);
	if (now - philo->last_meal > philo->var->tm_die)
		status = DIED;
	else if (philo->full)
		status = FULL;
	pthread_mutex_unlock(&(philo->meal_mut));
	return (status);
}

void	*check_death(void *arg)
{
	t_var	*var;
	int		i;
	int		all_full;
	t_status	status;

	var = (t_var *)arg;
	get_start(var);
	while (get_bool(&(var->start_mutex), &(var->start)))
	{
		i = 0;
		all_full = 0;
		while (i < var->nbr_ph)
		{
			status = is_philo_died(&(var->philos[i]));
			if (status == DIED)
			{
				console_status(&(var->philos[i]), DIED);
				set_bool(&(var->start_mutex), &(var->start), false);
				break;
			}
			if (status == FULL)
				all_full++;
			i++;
		}
		//printf("var must eat = %d, all full = %d\n", var->must_eat, all_full);
		if (var->must_eat != -1 && all_full == var->nbr_ph)
		{
			set_bool(&(var->start_mutex), &(var->start), false);
			console_status(&(var->philos[0]), FULL);
			break;
		}
		usleep(100);
	}
	//printf("finished loop in check death\n");
	//ft_cleanup(var, var->nbr_ph, var->nbr_ph);
	return (NULL);
}

/* Debug helper: print when a philosopher thread exits (helps ensure joins won't block). */

void	console_status(t_philo *philo, t_status status)
{
	pthread_mutex_lock(&(philo->var->write_mutex));
	printf("%lld %d ", get_ms_time(), philo->id);
	if (status == TAKE_FIRST_FORK)
	{
		if (philo->id % 2 == 0)
			printf("has taken the left fork\n");
		else
			printf("has taken the right fork\n");
	}
	if (status == TAKE_SECOND_FORK)
	{
		if (philo->id % 2 == 0)
			printf("has taken the right fork\n");
		else
			printf("has taken the left fork\n");
	}
	if (status == EAT)
		printf("is eating\n");
	if (status == SLEEP)
		printf("is sleeping\n");
	if (status == THINK)
		printf("is thinking\n");
	if (status == DIED)
		printf("died\n");
	pthread_mutex_unlock(&(philo->var->write_mutex));
}

void	eating(t_philo *philo)
{
	t_var	*var;

	var = philo->var;
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
	usleep(var->tm_eat);
	pthread_mutex_unlock(philo->first);
	pthread_mutex_unlock(philo->second); 
}

void	sleep_think(t_philo *philo)
{
	t_var	*var;
	var = philo->var;
	console_status(philo, SLEEP);
	usleep(var->tm_sleep);
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
		usleep(philo->var->tm_die);
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
