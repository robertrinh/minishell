/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   post_lexer.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/12 16:19:25 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/06/13 15:59:11 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*handle_pipe(t_token *current, int *i)
{
	if (current->next)
	{
		*i = 0;
		current = skip_operators(current);
		current = assign_cmd_arg(current, *i);
	}
	return (current);
}

static t_token	*handle_redirect(t_token *current)
{
	if (current->next)
	{
		current = skip_operators(current);
		current = assign_argfile_args(current);
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
		if (curr->type == PIPE)
		{
			curr = handle_pipe(curr, &i);
			continue ;
		}
		if (curr->type == REDIRECT)
		{
			curr = handle_redirect(curr);
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
