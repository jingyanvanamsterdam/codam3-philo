#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include "philo.h"

void	get_start(t_var *var)
{
	while (!get_bool(&(var->start_mutex), &(var->start)))
		usleep(100);
}





