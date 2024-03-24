/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 19:21:32 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/24 09:32:09 by quentinbeuk   ########   odam.nl         */
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
	shell->double_quote = 0;
	shell->single_quote = 0;
	while (shell->input[i])
	{
		if (shell->input[i] == D_QUOTE_CHAR)
			shell->double_quote += 1;
		if (shell->input[i] == S_QUOTE_CHAR)
			shell->single_quote += 1;
		i++;
	}
	return (SUCCESS);
}

static bool	is_quote_matched(t_shell *shell)
{
	if (count_quotes(shell) == SUCCESS)
	{
		if (is_even_int(shell->double_quote) == false
			&& shell->double_quote > 0)
			return (false);
		else if (is_even_int(shell->single_quote) == false
			&& shell->single_quote > 0)
			return (false);
		else
			return (true);
	}
	return (false);
}

int	contains_quote(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == D_QUOTE_CHAR)
			return (D_QUOTE_CHAR);
		if (str[i] == S_QUOTE_CHAR)
			return (S_QUOTE_CHAR);
		i++;
	}
	return (0);
}

t_validation	validate_quotes(t_shell *shell)
{
	if (contains_quote(shell->input) == 0)
		return (SUCCESS);
	if (is_quote_matched(shell) == false)
		return (FAILURE);
	return (SUCCESS);
}
