/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getter_setter.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdong <jdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/18 14:56:44 by jdong         #+#    #+#                 */
/*   Updated: 2026/01/26 12:55:17 by jingyandong   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo.h"

int	get_bool(t_mutex *mutex, int *value)
{
	int	res;

	pthread_mutex_lock(mutex);
	res = *value;
	pthread_mutex_unlock(mutex);
	return (res);
}

void	set_bool(t_mutex *mutex, int *dest, int value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}
