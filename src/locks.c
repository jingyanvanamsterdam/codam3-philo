#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include "philo.h"

void	get_start(t_var *var)
{
	pthread_mutex_lock(&(var->start_mutex));
	while (var->start == false)
	{
		pthread_mutex_unlock(&(var->start_mutex));
		usleep(100);
		pthread_mutex_lock(&(var->start_mutex));
	}
	pthread_mutex_unlock(&(var->start_mutex));
	//printf("start...");
}
