/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_matcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:00:03 by qbeukelm          #+#    #+#             */
/*   Updated: 2023/12/22 17:37:37 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool is_last_quote_single(t_shell *shell)
{
	t_token	*tokens_current;

	tokens_current = lst_rev(lst_copy(shell->tokens));
	// print_token(tokens_current);
	while (tokens_current)
	{
		if (ft_strrchr(tokens_current->value, 34))
			return (false);
		if (ft_strrchr(tokens_current->value, 39))
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
	printf("first quote: %d\n", is_first_quote_single(shell));
	printf("last quote: %d\n", is_last_quote_single(shell));
	if (is_first_quote_single(shell) == is_last_quote_single(shell))
		return (true);
	return (false);
}
