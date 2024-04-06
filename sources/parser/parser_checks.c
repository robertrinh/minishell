/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_checks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/18 21:07:32 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/04/06 15:41:51 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	contains_pipe(t_token *token)
{
	if (token->type == PIPE)
		return (true);
	return (false);
}

static bool contains_redirect(t_token *token)
{
	if (token->type == REDIRECT)
		return (true);
	return (false);
}

static bool	check_pipes(t_token *tokens)
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
		}
		current = current->next;
	}
	return (SUCCESS);
}

static bool	check_redirects(t_token *tokens)
{
	t_token		*current;

	current = tokens;
	while (current)
	{
		if (contains_redirect(current))
		{
			if (current->next == NULL)
				return (FAILURE);
		}
		current = current->next;
	}
	return (SUCCESS);
}

bool	parser_checks(t_token *tokens)
{
	if (tokens == NULL)
		return (FAILURE);
	if (check_pipes(tokens) == FAILURE)
		return (show_error_message(E_UNMATCHED_PIPE, C_RED, ""));
	if (check_redirects(tokens) == FAILURE)
		return (show_error_message(E_UNMATCHED_REDIRECT, C_RED, ""));
	return (SUCCESS);
}
