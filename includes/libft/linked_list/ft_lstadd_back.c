/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 15:52:38 by qtrinh        #+#    #+#                 */
/*   Updated: 2023/08/04 14:10:06 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = *lst;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	else
	{
		temp = ft_lstlast(*lst);
		temp->next = new;
	}
}
