/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_checks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/18 21:07:32 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/13 16:25:21 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	contains_pipe(t_token *token)
{
	if (token->type == PIPE)
		return (true);
	return (false);
}

static bool	contains_redirect(t_token_type type)
{
	if (type >= REDIRECT && type <= REDIR_OUT)
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
	char		*value;

	current = tokens;
	while (current)
	{
		if (contains_redirect(current->type))
		{
			if (current->next == NULL)
				return (FAILURE);
			value = current->next->value;
			if (ft_strnstr(value, OPERATORS, ft_strlen(value) + 3))
				return (FAILURE);
			if (ft_strnstr(OPERATORS, value, ft_strlen(value) + 3))
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
		return (show_error_message(E_PIPE, C_RED, "", X_FAILURE));
	if (check_redirects(tokens) == FAILURE)
		return (show_error_message(E_REDIRECT, C_RED, "", X_FAILURE));
	return (SUCCESS);
}
