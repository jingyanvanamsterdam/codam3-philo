#include <pthread.h>
#include "philo.h"
#include <stdbool.h>
#include <stdio.h> // prinft

bool	get_bool(t_mutex *mutex, bool *value)
{
	bool	res;

	pthread_mutex_lock(mutex);
	res = *value;
	//printf("check bool %d\n", res);
	pthread_mutex_unlock(mutex);
	return (res);
}

void	set_bool(t_mutex *mutex, bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	//printf("set bool get started%d \n", value);
	pthread_mutex_unlock(mutex);
}
