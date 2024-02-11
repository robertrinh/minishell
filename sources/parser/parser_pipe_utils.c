/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_pipe_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 22:29:50 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/02/11 13:05:22 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	contains_pipe(t_token *current)
{
	if (current->type == PIPE)
		return (true);
	return (false);
}

t_token	*locate_pipe_n(t_token *tokens_root, int pipe_count)
{
	int			i;
	t_token 	*current;
	
	i = 0;
	current = tokens_root;
	while (current)
	{
		if (current->type == PIPE)
		{
			if (i == pipe_count)
				return (current);
			i++;
		}
		if (current->next == NULL)
			return (NULL);
		
		current = current->next;
	}
	return (NULL);
}
