/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdong <jdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/30 16:05:56 by jdong         #+#    #+#                 */
/*   Updated: 2025/05/06 13:45:33 by jdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptrholder;

	ptrholder = (unsigned char *)s;
	while (n > 0)
	{
		*ptrholder = '\0';
		n--;
		ptrholder++;
	}
}
