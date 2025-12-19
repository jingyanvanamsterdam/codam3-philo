#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
//#include <sys/time.h>
#include <stdlib.h>
#include "philo.h"

void	*check_routine(void *arg)
{
	(void)arg;
	// start mutex wait for all the threads are created.
	// check all the t_philo last meal and check death time.
	return (NULL);
}

void	*routine(void *arg)
{
	(void)arg;
	// start mutex: wait for all the threads are created. 
	// wait for lock: get_left_fork(); get_right_fork();
	// eat: last_meal = get_ms_time(); usleep(var->tm_eat);
	// unlock
	// sleep: sleep = get_ms_time(); usleep(var->tm_sleep);
	// thinking: start thinking until die or get forks again. 
	return (NULL);
}
