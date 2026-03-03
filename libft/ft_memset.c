/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdong <jdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/30 16:05:26 by jdong         #+#    #+#                 */
/*   Updated: 2025/05/06 13:49:32 by jdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptrholder;

	ptrholder = (unsigned char *)s;
	if (n == 0)
		return (s);
	while (n > 0)
	{
		*ptrholder = (unsigned char)c;
		n--;
		ptrholder++;
	}
	return (s);
}
