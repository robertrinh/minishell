/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/01 14:47:56 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/03/20 19:11:29 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_builtin(char *cmd_value)
{
	int		i;

	i = 0;
	while (i < S_NUM_BUILTIN)
	{
		if (ft_strncmp(cmd_value, builtin_table[i].name, ft_strlen(builtin_table[i].name)) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	int		i;
	int		exit_status;

	i = 0;
	exit_status = 0;
	while (i < S_NUM_BUILTIN)
	{
		if (ft_strncmp(cmd->value, builtin_table[i].name, ft_strlen(cmd->value)) == 0)
		{
			exit_status = builtin_table[i].function(cmd, shell);
			return (exit_status);
		}
		i++;
	}
	return (1);
}
