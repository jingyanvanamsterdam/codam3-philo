/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoll.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jingyandong <jingyandong@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/20 15:30:28 by jingyandong   #+#    #+#                 */
/*   Updated: 2025/12/20 15:30:30 by jingyandong   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static char	*valid_input(char *nptr)
{
	int	len;
	char *nbr;
	
	len = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '+')
		nptr++;
	else if (*nptr == '-')
		return (ft_putstr_fd("Need possitive value.", 2), NULL);
	if (!ft_isdigit(*nptr))
		return (ft_putstr_fd("Input is not number", 2), NULL);
	nbr = nptr;
	while (ft_isdigit(*nptr))
	{
		len++;
		nptr++;
	}
	if (len > 10)
		return (ft_putstr_fd("Input is too big. Limit is INT_MAX", 2), NULL);
	return (nbr);
}

long long	ft_atoll(char *nptr)
{
	long long	res;
	char		*nbr;

	res = -1;
	nbr = valid_input(nptr);
	if (!nbr)
		return (res);
	while (ft_isdigit(*nptr))
	{
		res = (*nptr - '0') + res * 10;
		nptr++;
	}
	if (res > INT_MAX)
		return (ft_putstr_fd("Input is too big. Limit is INT_MAX", 2), -1);
	return (res);
}
