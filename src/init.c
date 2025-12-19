#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include "philo.h"

static void	prepare_forks(t_var *var)
{
	int	i;

	i = 0;
	var->forks = ft_calloc(var->nbr_ph, sizeof(t_fork));
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
	var->must_eat = 0;
	if (ac == 6)
		var->must_eat = ft_atoi(av[5]);
	var->threads = NULL;
	var->start = false;
	if (pthread_mutex_init(&(var->start_mutex), NULL) != 0)
	{
		perror("create start mutex: ");
		exit(EXIT_FAILURE);
	}
	prepare_forks(var);
	if (pthread_create(&(var->check_die), NULL, check_routine, var) != 0)
		ft_failure_exit("create check death thread.", var, var->nbr_ph, 0);
}

static void	init_philo(int i, t_var *var)
{
	var->philos[i].var = var;
	var->philos[i].full = false;
	var->philos[i].id = i;
	var->philos[i].last_meal = 0;
	var->philos[i].left = var->forks + i;
	var->philos[i].right = var->forks + ((i + 1) % var->nbr_ph);
	if (pthread_create(var->threads + i, NULL, routine, &(var->philos[i])) != 0)
		ft_failure_exit("creating thread: ", var, var->nbr_ph, i);
	var->philos[i].th_id = var->threads[i];
	printf("th add = %p -- ", var->threads[i]);
	printf("th adr = %p; id = %d, philo.left = %p; right = %p\n", var->philos[i].th_id, i, var->philos[i].left, var->philos[i].right);
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
	pthread_mutex_lock(&(var->start_mutex));
	var->start_tm = get_ms_time();
	var->start = true;
	pthread_mutex_unlock(&(var->start_mutex));
}
