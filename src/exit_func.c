#include "libft.h"
#include <pthread.h>
#include <stdlib.h>
#include "philo.h"
#include <errno.h>

static void	ft_join_threads(int th_i, t_var *var)
{
	int	i;

	i = -1;
	while (++i < th_i)
		if (pthread_join(var->threads[i], NULL) != 0)
			ft_putstr_fd("join threads fails", 2);
	free(var->threads);
}

static void	ft_destory_fork(int fork_i, t_var *var)
{
	int	i;

	i = -1;
	while (++i < fork_i)
		pthread_mutex_destroy(var->forks + i);
	free(var->forks);
}

/**
 * Join the checker thread first to ensure it isn't holding the
 * write mutex while we wait for philosopher threads to finish. 
 * */
void	ft_cleanup(t_var *var, int fork_i, int th_i)
{
	int i;

	if (th_i != 0)
		if (pthread_join(var->check_die, NULL) != 0)
			ft_putstr_fd("join threads fails", 2);
	if (var->threads)
		ft_join_threads(th_i, var);
	if (var->forks)
		ft_destory_fork(fork_i, var);
	i = -1;
	while (++i < th_i)
		pthread_mutex_destroy(&(var->philos[i].meal_mut));
	pthread_mutex_destroy(&(var->start_mutex));
	pthread_mutex_destroy(&(var->write_mutex));
	pthread_mutex_destroy(&(var->stop_mutex));
	if (var->philos)
		free(var->philos);
}

void	ft_failure_exit(char *mes, t_var *var, int fork_i, int th_i)
{
	ft_putstr_fd(mes, 2);
	if (fork_i != 0 || th_i != 0)
		ft_cleanup(var, fork_i, th_i);
	exit(EXIT_FAILURE);
}
