#include "libft.h"
#include <pthread.h>
#include <stdlib.h>
#include "philo.h"
#include <errno.h>

void	ft_cleanup(t_var *var, int fork_i, int th_i)
{
	int i;

	i = 0;
	if (var->threads)
	{
		while (i < th_i)
		{
			if (pthread_join(var->threads[i], NULL) != 0)
				ft_putstr_fd("join threads fails", 2);
			i++;
		}
		free(var->threads);
	}
	if (var->forks)
	{
		i = 0;
		while (i < fork_i)
		{
			pthread_mutex_destroy(var->forks + i);
			i++;
		}
		free(var->forks);
	}
	pthread_mutex_destroy(&(var->start_mutex));
}

void	ft_failure_exit(char *mes, t_var *var, int fork_i, int th_i)
{
	ft_putstr_fd(mes, 2);
	ft_cleanup(var, fork_i, th_i);
	exit(EXIT_FAILURE);
}
