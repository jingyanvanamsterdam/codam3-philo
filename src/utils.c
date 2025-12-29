#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include "philo.h"

long long	get_ms_time(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		perror("gettimeofday failed.");
		return (-1);
	}
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

void	get_start(t_var *var)
{
	while (!get_bool(&(var->start_mutex), &(var->start)))
		usleep(100);
}

static void	write_status(t_status status, int id)
{
	printf("%lld %d ", get_ms_time(), id);
	if (status == TAKE_FIRST_FORK)
	{
		if (id % 2 == 0)
			printf("has taken the left fork\n");
		else
			printf("has taken the right fork\n");
	}
	if (status == TAKE_SECOND_FORK)
	{
		if (id % 2 == 0)
			printf("has taken the right fork\n");
		else
			printf("has taken the left fork\n");
	}
	if (status == EAT)
		printf("is eating\n");
	if (status == SLEEP)
		printf("is sleeping\n");
	if (status == THINK)
		printf("is thinking\n");
	if (status == DIED)
		printf("died\n");
}

void	console_status(t_philo *philo, t_status status)
{
	t_var *var;
	
	var = philo->var;
	if (get_bool(&(var->stop_mutex), &(var->stop)) && status != DIED)
		return ;
	pthread_mutex_lock(&(var->write_mutex));
	write_status(status, philo->id);
	pthread_mutex_unlock(&(var->write_mutex));
}
