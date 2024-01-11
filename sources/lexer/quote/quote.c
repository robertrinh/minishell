/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/21 15:27:42 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/01/10 17:56:36 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

static bool is_even_int(int i)
{
	if (i % 2)
		return (false);
	return (true);
}

static bool is_quote_matched(t_shell *shell)
{
	count_quotes(shell);
	if (is_even_int(shell->cmd->double_quote) == false
		|| is_even_int(shell->cmd->single_quote) == false)
		return (false);
	if (is_outer_quote_match(shell))
		return (true);
	return (false);
}


t_token *quote_manager(t_shell *shell)
{
	printf("\n\n========quote manager========\n");
	
	// 1. Check matching quotes / exit
	printf("Is matched %d \n", is_quote_matched(shell));
	
	// 2. Tokenize quotes
	tokenize_quotes(shell);

	return (shell->tokens);
}

