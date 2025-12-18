/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jingyandong <jingyandong@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/23 12:51:25 by jingyandong   #+#    #+#                 */
/*   Updated: 2025/12/18 13:30:39 by jingyandong   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	long	number;
	int		sign;

	number = 0;
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
		number = (*nptr - '0') + number * 10;
		nptr++;
	}
	return ((int)(sign * number));
}
