/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/03 09:41:20 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/24 15:22:51 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

int	exit_shell(t_cmd *cmd, t_shell *shell)
{
	if (shell->cmd_table->cmd_count == 1)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (cmd->arg_count > 1)
		return (show_error_message(E_ARG_ERR, shell, "", X_FAILURE), 1);
	if (cmd->arg_count == 1)
	{
		if (ft_isnumber(cmd->args[0]) == false || ft_strlen(cmd->args[0]) > 19)
			exit_with_message(E_NUMERIC_ERR, shell, X_NUMERIC_ERR);
		else
			shell->exit_code = ft_atoi(cmd->args[0]) % 256;
	}
	exit(shell->exit_code);
}
