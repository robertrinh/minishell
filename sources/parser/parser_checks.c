/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_checks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/18 21:07:32 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/01/18 21:34:18 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		check_pipes(t_token *tokens)
{
	t_token		*current;

	current = tokens;
	while (current)
	{
		if (contains_pipe(current))
		{
			// next is nothing
			if (current->next == NULL)
				return (FAILURE);
			
			// next is pipe
			else if (contains_pipe(current->next))
				return (FAILURE);
		}
		current = current->next;
	}
	return (SUCCESS);
}
