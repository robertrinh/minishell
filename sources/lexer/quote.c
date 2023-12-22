/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:27:42 by qbeukelm          #+#    #+#             */
/*   Updated: 2023/12/22 17:39:17 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	quotes_per_string(t_token *tokens_current, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (tokens_current->value[i])
	{
		if (tokens_current->value[i] == c)
			count++;
		i++;
	}
	return (count);
}

static void	count_quotes(t_shell *shell)
{
	t_token	*tokens_current;

	tokens_current = shell->tokens;
	while (tokens_current)
	{
		if (ft_strchr(tokens_current->value, 34))
			shell->cmd->double_quote += quotes_per_string(tokens_current, 34);
		if (ft_strchr(tokens_current->value, 39))
			shell->cmd->single_quote += quotes_per_string(tokens_current, 39);
		tokens_current = tokens_current->next;
	}
}

static bool is_quote_matched(t_shell *shell)
{
	count_quotes(shell);
	if (shell->cmd->double_quote % 2 || shell->cmd->single_quote % 2)
		return (false);
	if (is_outer_quote_match(shell))
		return (true);
	return (false);
}



t_token *quote_manager(t_shell *shell)
{
	printf("\n\n========quote manager========\n");
	
	printf("is matched %d \n", is_quote_matched(shell));
	printf("Double: %d, \nSingle %d \n", shell->cmd->double_quote, shell->cmd->single_quote);
	return (shell->tokens);
}

