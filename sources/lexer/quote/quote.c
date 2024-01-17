/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 19:21:32 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/01/17 15:56:41 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	is_even_int(int i)
{
	if (i % 2)
		return (false);
	return (true);
}

static int	count_quotes(t_shell *shell)
{
	int		i;

	i = 0;
	shell->cmd->double_quote = 0;
	shell->cmd->single_quote = 0;
	while (shell->input[i])
	{
		if (shell->input[i] == 34)
			shell->cmd->double_quote += 1;
		if (shell->input[i] == 39)
			shell->cmd->single_quote += 1;
		i++;
	}
	return (SUCCESS);
}

static bool	is_quote_matched(t_shell *shell)
{
	if (count_quotes(shell) == SUCCESS)
	{
		if (is_even_int(shell->cmd->double_quote) == false
			&& shell->cmd->double_quote > 0)
			return (false);
		else if (is_even_int(shell->cmd->single_quote) == false
			&& shell->cmd->single_quote > 0)
			return (false);
		else
			return (true);
	}
	return (false);
}

static bool	contains_quote(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			return (true);
		i++;
	}
	return (false);
}

int	quote_manager(t_shell *shell)
{
	// Continue if no quote is found
	if (contains_quote(shell->input) == false)
		return (SUCCESS);
	if (is_quote_matched(shell) == false)
		return (FAILURE);
	return (SUCCESS);
}
