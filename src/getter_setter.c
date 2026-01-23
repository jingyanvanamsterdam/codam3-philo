/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getter_setter.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdong <jdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/18 14:56:44 by jdong         #+#    #+#                 */
/*   Updated: 2026/01/18 15:09:16 by jdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo.h"
#include <stdbool.h>
#include <stdio.h> // prinft

bool	get_bool(t_mutex *mutex, bool *value)
{
	bool	res;

	pthread_mutex_lock(mutex);
	res = *value;
	pthread_mutex_unlock(mutex);
	return (res);
}

void	set_bool(t_mutex *mutex, bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}
