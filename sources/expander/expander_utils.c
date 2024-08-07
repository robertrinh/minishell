/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/23 21:54:16 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/08/01 17:50:23 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_multiple_expand_chars(char *arg, size_t *i)
{
	size_t	start;

	start = *i;
	while (arg[*i] == EXPAND_CHAR)
		(*i)++;
	if (*i > start)
		(*i)--;
}

bool	check_expand_char(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if ((arg[i] == S_QUOTE_CHAR) || (arg[i] == D_QUOTE_CHAR)
			|| arg[i] == EXPAND_CHAR)
			return (true);
		i++;
	}
	return (false);
}

bool	expand_exit_code(t_vec *vec, t_shell *shell)
{
	char	*exit_code_string;

	exit_code_string = ft_itoa(shell->exit_code);
	if (exit_code_string == NULL)
		return (show_error(E_MALLOC, shell, "exit_code", 1), FAILURE);
	if (!ft_vec_push_str(vec, exit_code_string))
		return (show_error(E_MALLOC, shell, "vec push", 1), FAILURE);
	free(exit_code_string);
	return (SUCCESS);
}
