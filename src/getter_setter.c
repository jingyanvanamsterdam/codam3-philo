#include <pthread.h>
#include "philo.h"
#include <stdbool.h>

bool	get_bool(t_fork *mutex, bool *value)
{
	bool	res;

	pthread_mutex_lock(mutex);
	res = *value;
	pthread_mutex_unlock(mutex);
	return (res);
}

bool	set_bool(t_fork *mutex, bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

