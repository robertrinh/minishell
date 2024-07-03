/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   post_lexer.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/12 16:19:25 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/06/29 09:47:54 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*handle_pipe_or_redirect(t_token *current, int *i)
{
	if (current->type == PIPE)
	{
		if (current->next)
		{
			*i = 0;
			current = skip_operators(current);
			current = assign_cmd_arg(current, *i);
		}
	}
	else if (current->type == REDIRECT)
	{
		if (current->next)
		{
			current = skip_operators(current);
			current = assign_argfile_args(current);
		}
	}
	return (current);
}

static bool	assign_lexer_types(t_token *tokens)
{
	int			i;
	t_token		*curr;

	i = 0;
	curr = tokens;
	while (curr)
	{
		if ((curr->type == NONE && is_special_type(curr->type) == false))
			curr = assign_cmd_arg(curr, i);
		if (curr->type == COMMAND && curr->next != NULL)
			if (curr->next->type == D_QUOTE || curr->next->type == S_QUOTE)
				curr = assign_cmd_arg(curr->next, i++);
		if (curr->type == PIPE || curr->type == REDIRECT)
		{
			curr = handle_pipe_or_redirect(curr, &i);
			continue ;
		}
		i++;
		curr = curr->next;
	}
	return (SUCCESS);
}

bool	post_lexer(t_token *tokens)
{
	assign_lexer_types(tokens);
	assign_redirect_types(tokens);
	return (SUCCESS);
}
