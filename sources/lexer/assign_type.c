/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   assign_type.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/12 14:27:34 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/02/25 11:08:54 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	contains_redirect(char *value)
{
	int	i;

	i = 0;
	while (REDIRECTS[i])
	{
		if (ft_strchr(value, REDIRECTS[i]))
			return (true);
		i++;
	}
	return (false);
}

static t_token_type	assign_redirect_type(char *value)
{
	if (ft_strncmp(value, ">", 2) == 0)
		return (REDIR_OUT);
	else if (ft_strncmp(value, ">>", 2) == 0)
		return (REDIR_OUT);
	else if (ft_strncmp(value, "<", 2) == 0)
		return (REDIR_IN);
	else if (ft_strncmp(value, "<<", 2) == 0)
		return (REDIR_IN_APPEND);
	// TODO add END_OF_FILE
	return (REDIRECT);
}

bool	assign_redirect_types(t_token *tokens)
{
	t_token *current;

	current = tokens;
	while (current)
	{
		if (current->type == REDIRECT)
			current->type = assign_redirect_type(current->value);
		if (current->type == REDIR_IN_APPEND)
			current->next->type = END_OF_FILE;
		current = current->next;
	}
	return (SUCCESS);
}

t_token_type	assign_type(char *value)
{
	if (contains_redirect(value))
		return (REDIRECT);
	else if (ft_strchr(value, '|'))
		return (PIPE);
	return (NONE);
}
