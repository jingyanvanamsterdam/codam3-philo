/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdong <jdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/18 14:57:11 by jdong         #+#    #+#                 */
/*   Updated: 2026/01/21 19:47:35 by jdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "philo.h"

/** 	
 * ./philo time_die, time_eat, time_sleep, [must_eat]
 * 
 * Wait for threads and cleanup resources. 
 * Without joining, 
 * main returns and the process exits which terminates all threads*/
int	main(int ac, char *av[])
{
	t_var	var;

	if (ac < 5 || ac > 7)
		return (ft_putstr_fd("input error", 2), 1);
	init_var(ac, av, &var);
	create_philos_threads(&var);
	ft_cleanup(&var, var.nbr_ph, var.nbr_ph);
	return (0);
}
