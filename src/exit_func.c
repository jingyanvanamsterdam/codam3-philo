#include "libft.h"
#include <pthread.h>
#include <stdlib.h>
#include "philo.h"
#include <errno.h>

void	ft_join_threads(int th_i, t_var *var)
{
	int	i;

	i = 0;
	while (i < th_i)
	{
		if (pthread_join(var->threads[i], NULL) != 0)
			ft_putstr_fd("join threads fails", 2);
		i++;
	}
	free(var->threads);
}

void	ft_destory_fork(int fork_i, t_var *var)
{
	int	i;

	i = 0;
	while (i < fork_i)
	{
		pthread_mutex_destroy(var->forks + i);
		i++;
	}
	free(var->forks);
}

void	ft_cleanup(t_var *var, int fork_i, int th_i)
{
	int i;

	i = 0;
	if (var->threads)
		ft_join_threads(th_i, var);
	if (th_i != 0)
		pthread_join(var->check_die, NULL);
	if (var->forks)
		ft_destory_fork(fork_i, var);
	while (i < th_i)
		pthread_mutex_destroy(&(var->philos[i].meal_mut));
	pthread_mutex_destroy(&(var->start_mutex));
	pthread_mutex_destroy(&(var->write_mutex));
}

void	ft_failure_exit(char *mes, t_var *var, int fork_i, int th_i)
{
	ft_putstr_fd(mes, 2);
	ft_cleanup(var, fork_i, th_i);
	exit(EXIT_FAILURE);
}
