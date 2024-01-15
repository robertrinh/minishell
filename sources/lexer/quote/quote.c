/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 19:21:32 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/01/16 00:06:36 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_quote(char c)
{
	if (c == 34)
		return (34);
	else if (c == 39)
		return (39);
	return (0);
}

static bool is_even_int(int i)
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

static bool is_quote_matched(t_shell *shell)
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

static bool	contains_quote(const char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
			return (true);
		i++;
	}
	return (false);
}

int		quote_manager(t_shell *shell)
{
	// Continue if no quote is found
	if (contains_quote(shell->input) == false)
		return (SUCCESS);

	if (is_quote_matched(shell) == false)
		return (FAILURE);

	return (SUCCESS);
}
