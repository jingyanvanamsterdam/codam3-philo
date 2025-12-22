#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include "philo.h"

void	get_start(t_var *var)
{
	while (!get_bool(&(var->start_mutex), &(var->start)))
		usleep(100);
	//printf("start...");
}

void	console_status(t_philo *philo, t_status status)
{
	pthread_mutex_lock(&(philo->var->write_mutex));
	printf("%lld %d ", get_ms_time(), philo->id);
	if (status == TAKE_FIRSt_mutex)
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
	console_status(philo, TAKE_FIRSt_mutex);
	pthread_mutex_lock(philo->second);
	console_status(philo, TAKE_SECOND_FORK);
	pthread_mutex_lock(&(philo->meal_mut));
	philo->last_meal = get_ms_time();
	pthread_mutex_unlock(&(philo->meal_mut));
	console_status(philo, EAT);
	if (++philo->meals == var->must_eat && var->must_eat != 0)
		philo->full = true;
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