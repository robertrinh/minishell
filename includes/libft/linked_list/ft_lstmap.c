/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 17:18:38 by qtrinh        #+#    #+#                 */
/*   Updated: 2022/11/17 17:07:50 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_elem;

	new_elem = NULL;
	while (lst)
	{
		new_list = ft_lstnew(f(lst->content));
		if (new_list == NULL)
		{
			ft_lstclear(&new_elem, del);
			return (NULL);
		}
		else
			ft_lstadd_back(&new_elem, new_list);
		lst = lst->next;
	}
	return (new_elem);
}

/* 
Return value 
The new list.
NULL if the allocation fails.

Description:
Iterates the list ’lst’ and applies the function
’f’ on the content of each node. Creates a new
list resulting of the successive applications of
the function ’f’. The ’del’ function is used to
delete the content of a node if needed. */