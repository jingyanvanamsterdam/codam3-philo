/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routines.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdong <jdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/18 14:57:26 by jdong         #+#    #+#                 */
/*   Updated: 2026/01/26 13:51:06 by jingyandong   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "philo.h"

static t_status	check_philo_status(t_philo *philo, int *all_full)
{
	long long	now;
	t_status	status;
	t_var		*var;

	now = get_us_time();
	status = 0;
	var = philo->var;
	pthread_mutex_lock(&(philo->meal_mut));
	if (philo->full && var->must_eat != -1
		&& ++(*all_full) == var->nbr_ph)
		status = FULL;
	else if ((now - philo->last_meal) > philo->var->tm_die)
		status = DIED;
	pthread_mutex_unlock(&(philo->meal_mut));
	if (status == FULL)
		set_bool(&(var->stop_mutex), &(var->stop), 1);
	if (status == DIED
		&& !get_bool(&(var->stop_mutex), &(var->stop)))
	{
		set_bool(&(var->stop_mutex), &(var->stop), 1);
		console_status(philo, DIED);
	}
	return (status);
}

void	*check_death(void *arg)
{
	t_var		*var;
	int			i;
	int			all_full;
	t_status	status;

	var = (t_var *)arg;
	get_start(var);
	while (!get_bool(&(var->stop_mutex), &(var->stop)))
	{
		i = -1;
		all_full = 0;
		while (++i < var->nbr_ph)
		{
			status = check_philo_status(&(var->philos[i]), &all_full);
			if (status == DIED || status == FULL)
				break ;
		}
		usleep(100);
	}
	return (NULL);
}

/**
 * If there is an odd amount of philos, let the odd nbr (the ones more) to wait 
 * then it will avoid the situation where one even philo cannot take any forks;
 * because of its odd neighbor always get a fork. usleep(1000) = 1ms
 */
int	eating(t_philo *philo)
{
	t_var	*var;

	var = philo->var;
	if (philo->id % 2 != 0)
		usleep(1000);
	pthread_mutex_lock(philo->first);
	console_status(philo, TAKE_FIRST_FORK);
	pthread_mutex_lock(philo->second);
	pthread_mutex_lock(&(philo->meal_mut));
	philo->last_meal = get_us_time();
	console_status(philo, TAKE_SECOND_FORK);
	console_status(philo, EAT);
	if (++philo->meals == var->must_eat && var->must_eat != -1)
		philo->full = 1;
	pthread_mutex_unlock(&(philo->meal_mut));
	pthread_mutex_unlock(philo->second);
	pthread_mutex_unlock(philo->first);
	if (!ft_usleep(var, EAT))
		return (0);
	return (1);
}

void	sleep_think(t_philo *philo)
{
	t_var	*var;

	var = philo->var;
	console_status(philo, SLEEP);
	if (!ft_usleep(var, SLEEP))
		return ;
	console_status(philo, THINK);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_var	*var;

	philo = (t_philo *)arg;
	var = philo->var;
	get_start(var);
	if (philo->var->nbr_ph == 1)
	{
		console_status(philo, TAKE_FIRST_FORK);
		ft_usleep(var, DIED);
		return (NULL);
	}
	while (!get_bool(&(var->stop_mutex), &(var->stop)))
	{
		if (get_bool(&(philo->meal_mut), &(philo->full)))
			break ;
		if (!eating(philo))
			return (NULL);
		sleep_think(philo);
	}
	return (NULL);
}
