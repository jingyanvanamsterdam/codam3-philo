/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoll.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jingyandong <jingyandong@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/18 13:32:58 by jingyandong   #+#    #+#                 */
/*   Updated: 2025/12/18 13:33:33 by jingyandong   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long ft_atoll(char *nptr)
{
	long long	nbr;
	long long	sign;

	nbr = 0;
	sign = 1;
		while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nbr = (*nptr - '0') + nbr * 10;
		nptr++;
	}
	return (sign * nbr);
}
