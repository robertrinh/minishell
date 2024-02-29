/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:07:32 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/02/29 13:38:28 by qbeukelm         ###   ########.fr       */
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
	if (check_pipes(tokens) == FAILURE)
		return (exit_with_message(ERROR_UNMATCHED_PIPE, RED, 0));
	if (check_redirects(tokens) == FAILURE)
		return (exit_with_message(ERROR_UNMATCHED_REDIRECT, RED, 0));
	return (SUCCESS);
}
