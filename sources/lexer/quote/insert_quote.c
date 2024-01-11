/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   insert_quote.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 14:56:48 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/01/11 16:56:27 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	trim_list(t_token *first, t_token *last)
{
	t_token	*current;
	
	if (first->next->i == last->i)
		return (FAILURE);
	else
	{
		current = first;
		current = current->next;
		while (current)
		{
			if (current->next->i == last->i)
			{
				free(current->value);
				free(current);
				break ;
			}
			free(current);
			current = current->next;
		}
	}
	return (SUCCESS);
}

static t_token	*locate_last(t_token *first, t_token *last)
{
	t_token	*current;

	current = first;
	while (current)
	{
		if (current->i == last->i)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	insert_quote(t_token *first, t_token *last, char *before, char *after)
{
	t_token	*original_last;
	
	if (first && last)
	{
		first->value = before;
		if (trim_list(first, last) == SUCCESS)
		{
			original_last = locate_last(first, last);
			first->next = original_last;
			first->next->value = after;
		}
		else
			first->next->value = after;
	}
}
