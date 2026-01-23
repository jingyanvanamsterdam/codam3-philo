/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdong <jdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/18 14:56:59 by jdong         #+#    #+#                 */
/*   Updated: 2026/01/23 19:01:00 by jdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "philo.h"

static void	prepare_forks(t_var *var)
{
	int	i;

	i = 0;
	var->forks = ft_calloc(var->nbr_ph, sizeof(t_mutex));
	if (!var->forks)
		ft_failure_exit("malloc forks", var, 0, 0);
	while (i < var->nbr_ph)
	{
		if (pthread_mutex_init(var->forks + i, NULL) != 0)
			ft_failure_exit("creating forks", var, i, 0);
		i++;
	}
}

void	init_var(int ac, char **av, t_var *var)
{
	//check int Max and longlong max
	var->nbr_ph = ft_atoi(av[1]);
	var->tm_die = ft_atoll(av[2]) * 1000;
	var->tm_eat = ft_atoll(av[3]) * 1000;
	var->tm_sleep = ft_atoll(av[4]) * 1000;
	if (var->nbr_ph <= 0 || var->tm_die <= 0 || var->tm_eat <= 0
		|| var->tm_sleep < 0)
		exit(EXIT_FAILURE);
	if (var->nbr_ph > 200)
		ft_failure_exit("Number of philo should be less 200", var, 0, 0);
	var->must_eat = -1;
	if (ac == 6)
	{
		var->must_eat = ft_atoi(av[5]);
		if (var->must_eat == 0)
			ft_failure_exit("Must eat value cannot be 0", var, 0, 0);
	}
	var->threads = NULL;
	var->start = false;
	var->stop = false;
	if (pthread_mutex_init(&(var->start_mutex), NULL) != 0
		|| pthread_mutex_init(&(var->write_mutex), NULL) != 0
		|| pthread_mutex_init(&(var->stop_mutex), NULL) != 0)
		ft_failure_exit("init start mutex", var, var->nbr_ph, 0);
	prepare_forks(var);
}

static void	init_philo(int i, t_var *var)
{
	t_philo	*philo;

	philo = &(var->philos[i]);
	philo->var = var;
	philo->full = false;
	philo->id = i + 1;
	philo->last_meal = get_us_time();
	philo->meals = 0;
	if (i % 2 != 0)
	{
		philo->first = var->forks + i;
		philo->second = var->forks + ((i + 1) % var->nbr_ph);
	}
	else
	{
		philo->first = var->forks + ((i + 1) % var->nbr_ph);
		philo->second = var->forks + i;
	}
	if (pthread_mutex_init(&(philo->meal_mut), NULL) != 0)
		ft_failure_exit("createing mutex", var, var->nbr_ph, i);
	if (pthread_create(var->threads + i, NULL, routine, &(var->philos[i])) != 0)
		ft_failure_exit("creating thread", var, var->nbr_ph, i);
	philo->th_id = var->threads[i];
}

/**
 * Create threads one by one.
 * After all the philos are created, get last_eat time with start time.
 * Then create Check_death thread.
 */
void	create_philos_threads(t_var *var)
{
	int	i;

	var->threads = (pthread_t *)malloc(var->nbr_ph * sizeof(pthread_t));
	if (!var->threads)
		ft_failure_exit("malloc for threads", var, var->nbr_ph, 0);
	var->philos = (t_philo *)malloc(var->nbr_ph * sizeof(t_philo));
	if (!var->philos)
		ft_failure_exit("malloc for threads", var, var->nbr_ph, 0);
	i = -1;
	while (++i < var->nbr_ph)
		init_philo(i, var);
	i = -1;
	var->start_tm = get_us_time();
	while (++i < var->nbr_ph)
		var->philos[i].last_meal = var->start_tm;
	set_bool(&(var->start_mutex), &(var->start), true);
	if (pthread_create(&(var->check_die), NULL, check_death, var) != 0)
		ft_failure_exit("create check death thread", var, var->nbr_ph, 0);
}
