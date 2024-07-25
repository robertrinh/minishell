/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/23 21:54:16 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/07/25 17:00:11 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void skip_multiple_expand_chars(char *arg, size_t *i)
{
    size_t	start;
	
	start = *i;
    while (arg[*i] == EXPAND_CHAR)
        (*i)++;
    if (*i > start)
        (*i)--;
}

int	count_expand(char *arg)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (arg[i] == EXPAND_CHAR)
			count++;
		i++;
	}
	return (count);
}

bool	should_not_expand(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if ((arg[i] == S_QUOTE_CHAR) || (arg[i] == D_QUOTE_CHAR)
			|| arg[i] == EXPAND_CHAR)
			return (false);
		i++;
	}
	return (true);
}

bool	expand_exit_code(t_vec *vec, t_shell *shell)
{
	char	*exit_code_string;

	exit_code_string = ft_itoa(shell->exit_code);
	if (exit_code_string == NULL)
		return (show_error_message(E_MALLOC, shell, "exit_code", 1), FAILURE);
	if (!ft_vec_push_str(vec, exit_code_string))
		return (show_error_message(E_MALLOC, shell, "vec push", 1), FAILURE);
	free(exit_code_string);
	return (SUCCESS);
}
