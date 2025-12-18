/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jingyandong <jingyandong@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/04 18:07:54 by jingyandong   #+#    #+#                 */
/*   Updated: 2025/05/08 12:14:43 by jingyandong   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*node;
	t_list	*temp;
	void	*new_content;

	if (!lst || !f || !del)
		return (NULL);
	temp = lst;
	new_lst = NULL;
	while (temp)
	{
		new_content = f(temp->content);
		node = ft_lstnew(new_content);
		if (!node)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, node);
		temp = temp->next;
	}
	return (new_lst);
}
