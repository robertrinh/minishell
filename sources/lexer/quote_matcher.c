/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_matcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:00:03 by qbeukelm          #+#    #+#             */
/*   Updated: 2024/01/06 15:16:07 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	last_quote(t_token *current)
{
	int	len;

	len = ft_strlen(current->value);
	while (len >= 0)
	{
		if (current->value[len] == 34 || current->value[len] == 39)
			return (current->value[len]);
		len--;
	}
	return (0);
}

static bool is_last_quote_single(t_shell *shell)
{
	t_token	*tokens_current;

	tokens_current = lst_rev(lst_copy(shell->tokens));
	while (tokens_current)
	{
		if (last_quote(tokens_current) == 34)
			return (false);
		if (last_quote(tokens_current) == 39)
			return (true);
		tokens_current = tokens_current->next;
	}
	return (true);
}

static bool	is_first_quote_single(t_shell *shell)
{
	t_token	*tokens_current;

	tokens_current = shell->tokens;
	while (tokens_current)
	{
		if (ft_strchr(tokens_current->value, 34))
			return (false);
		if (ft_strchr(tokens_current->value, 39))
			return (true);
		tokens_current = tokens_current->next;
	}
	return (true);
}

bool	is_outer_quote_match(t_shell *shell)
{
	if (is_first_quote_single(shell) == is_last_quote_single(shell))
		return (true);
	return (false);
}
