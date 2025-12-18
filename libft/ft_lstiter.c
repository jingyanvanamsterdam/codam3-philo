/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstiter.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jingyandong <jingyandong@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/04 18:02:54 by jingyandong   #+#    #+#                 */
/*   Updated: 2025/05/06 13:48:02 by jdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
