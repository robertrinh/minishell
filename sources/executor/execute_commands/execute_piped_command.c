/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_piped_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:13:57 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/09/02 13:28:11 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_validation	execute_piped_command(t_shell *shell, t_cmd *cmd)
{
	char	*cmd_value;
	char	*cmd_path;
	char	**cmd_and_args;

	cmd_value = cmd->value;
	cmd_path = cmd->cmd_path;
	cmd_and_args = cmd->cmd_and_args;
	if (is_child_builtin(cmd_value))
		exec_builtin(shell, cmd);
	if (cmd_path == NULL)
		exit(shell->exit_code);
	else if (execve(cmd_path, cmd_and_args, shell->envp) == -1)
	{
		show_error(E_EXECVE, shell, cmd_value, X_FAILURE);
		exit(shell->exit_code);
	}
	return (SUCCESS);
}
