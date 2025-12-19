#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
//#include <sys/time.h>
#include <stdlib.h>
#include "philo.h"

void	*check_routine(void *arg)
{
	t_var	*var;

	var = (t_var *)arg;
	get_start(var);
	// start mutex wait for all the threads are created.
	// check all the t_philo last meal and check death time.
	return (NULL);
}

void	*routine(void *arg)
{
	// start mutex: wait for all the threads are created. 
	t_philo *philo;
	t_var	*var;

	philo = (t_philo *)arg;
	var = philo->var;
	get_start(var);
	// wait for lock: get_left_fork(); get_right_fork();
	// eat: last_meal = get_ms_time(); usleep(var->tm_eat);
	// unlock
	// sleep: sleep = get_ms_time(); usleep(var->tm_sleep);
	// thinking: start thinking until die or get forks again. 
	return (NULL);
}
