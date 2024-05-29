/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   post_lexer.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/12 16:19:25 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/05/29 16:29:29 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_special_type(t_token_type type)
{
	if (type == PIPE || type == REDIRECT)
		return (true);
	return (false);
}

static t_token	*skip_operators(t_token *current)
{
	while (current)
	{
		if (is_special_type(current->type) == false)
			return (current);
		if (current->next)
			current = current->next;
		else
			return (current);
	}
	return (current);
}

static t_token	*assign_argfile_args(t_token *current)
{
	current->type = ARGFILE;
	while (current)
	{
		if (is_special_type(current->type) == true)
			return (current);
		if (current->type == NONE)
			current->type = ARGUMENT;
		if (current->next)
			current = current->next;
		else
			return (current);
	}
	return (current);
}

static t_token	*assign_cmd_arg(t_token *current, int i)
{
	if (current->type == NONE || i == 0)
		current->type = COMMAND;
	else if (current->next)
		current = current->next;
	while (current)
	{
		if (current->type == NONE || i > 0)
		{
			current->type = ARGUMENT;
			current = current->next;
		}
		if (is_special_type(current->type) == true)
			return (current);
		if (current->next)
			current = current->next;
		else
			return (current);
	}
	return (current);
}

static bool	assign_lexer_types(t_token *tokens)
{
	int			i;
	t_token		*current;

	i = 0;
	current = tokens;
	while (current)
	{
		if (current->type == S_QUOTE || current->type == D_QUOTE)
		{
			i++;
			current = assign_cmd_arg(current, i);
		}
		if (current->type == NONE && is_special_type(current->type) == false)
		{
			i = 0;
			current = assign_cmd_arg(current, i);
		}
		if (current->type == PIPE)
		{
			if (current->next)
			{
				i = 0;
				current = skip_operators(current);
				current = assign_cmd_arg(current, i);
			}
		}
		if (current->type == REDIRECT)
		{
			if (current->next)
			{
				current = skip_operators(current);
				current = assign_argfile_args(current);
				continue ;
			}
		}
		i++;
		current = current->next;
	}
	return (SUCCESS);
}

bool	post_lexer(t_token *tokens)
{
	assign_lexer_types(tokens);
	assign_redirect_types(tokens);
	return (SUCCESS);
}
