/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jingyandong <jingyandong@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/26 13:48:32 by jingyandong   #+#    #+#                 */
/*   Updated: 2026/01/26 13:55:17 by jingyandong   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

int	ft_parse_int(char *nptr, int *res)
{
	long	number;
	int		digit;

	number = 0;
	if (!nptr || *nptr == '\0')
		return (0);
	while (*nptr)
	{
		if (*nptr < '0' || *nptr > '9')
			return (0);
		digit = *nptr - '0';
		if (number > (INT_MAX - digit) / 10)
			return (0);
		number = number * 10 + digit;
		nptr++;
	}
	if (number <= 0)
		return (0);
	*res = (int)number;
	return (1);
}

int	ft_parse_ll(char *nptr, long long *res)
{
	long long	number;
	int			digit;

	number = 0;
	if (!nptr || *nptr == '\0')
		return (0);
	while (*nptr)
	{
		if (*nptr < '0' || *nptr > '9')
			return (0);
		digit = *nptr - '0';
		if (number > (LLONG_MAX - digit) / 10)
			return (0);
		number = number * 10 + digit;
		nptr++;
	}
	if (number <= 0 || number * 1000 > LLONG_MAX)
		return (0);
	*res = number * 1000;
	return (1);
}
