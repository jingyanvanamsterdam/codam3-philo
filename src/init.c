#include "libft.h"
//#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
//#include <sys/time.h>
#include <stdlib.h>
#include "philo.h"

static void	prepare_forks(t_var *var)
{
	int	i;

	i = 0;
	var->forks = ft_calloc(var->nbr_ph, sizeof(t_mutex));
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
	var->must_eat = -1;
	if (ac == 6)
		var->must_eat = ft_atoi(av[5]);
	if (var->nbr_ph < 0 || var->tm_die < 0 || var->tm_eat < 0
		|| var->tm_sleep < 0)
		exit(EXIT_FAILURE);
	var->threads = NULL;
	var->start = false;
	if (pthread_mutex_init(&(var->start_mutex), NULL) != 0
		|| pthread_mutex_init(&(var->write_mutex), NULL) != 0)
		ft_failure_exit("create check death thread.", var, var->nbr_ph, 0);
	prepare_forks(var);
	if (pthread_create(&(var->check_die), NULL, check_death, var) != 0)
		ft_failure_exit("create check death thread.", var, var->nbr_ph, 0);
}

static void	init_philo(int i, t_var *var)
{
	t_philo	*philo;

	philo = &(var->philos[i]);
	philo->var = var;
	philo->full = false;
	philo->id = i;
	philo->last_meal = get_ms_time();
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
		ft_failure_exit("createing mutex: ", var, var->nbr_ph, i);
	if (pthread_create(var->threads + i, NULL, routine, &(var->philos[i])) != 0)
		ft_failure_exit("creating thread: ", var, var->nbr_ph, i);
	philo->th_id = var->threads[i];
	printf("th add = %p -- ", var->threads[i]);
	printf("th adr = %p; id = %d, philo.first = %p; second = %p\n", philo->th_id, i, philo->first, philo->second);
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
		init_philo(i, var);
		i++;
	}
	set_bool(&(var->start_mutex), &(var->start), true);
	var->start_tm = get_ms_time();
}
