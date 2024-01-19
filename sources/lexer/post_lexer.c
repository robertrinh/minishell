/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:19:25 by qbeukelm          #+#    #+#             */
/*   Updated: 2024/01/19 16:54:38 by qbeukelm         ###   ########.fr       */
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

static t_token	*assign_cmd_arg(t_token *current)
{
	if (current->type == NONE)
		current->type = COMMAND;
	else if (current->next)
		current = current->next;
	while (current)
	{
		if (current->type == NONE)
			current->type = ARGUMENT;
		if (is_special_type(current->type) == true)
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

bool	post_lexer(t_shell *shell)
{
	t_token		*current;

	current = shell->tokens;
	while (current)
	{
		if (current->type == NONE)
			current = assign_cmd_arg(current);
		if (current->type == PIPE)
		{
			if (current->next)
			{
				current = skip_operators(current);
				current = assign_cmd_arg(current);
			}
		}
		if (current->type == REDIRECT)
		{
			if (current->next)
			{
				current = skip_operators(current);
				current = assign_argfile_args(current);
			}
		}
		current = current->next;
	}
	return (SUCCESS);
}

// TODO add to unit tests
// >> word | and some
// >> word and | and some more <<> this
