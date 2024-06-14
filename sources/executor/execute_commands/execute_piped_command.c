/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_piped_command.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/22 21:13:57 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/13 15:44:33 by qtrinh        ########   odam.nl         */
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
	if (is_builtin(shell->builtin_child, cmd, B_NUM_CHILD))
		exec_builtin(shell->builtin_child, cmd, shell, B_NUM_CHILD);
	if (cmd_path == NULL)
		exit(g_exit_code);
	else if (execve(cmd_path, cmd_and_args, shell->envp) == -1)
	{
		show_error_message(E_EXECVE, C_RED, cmd_value, X_FAILURE);
		exit(g_exit_code);
	}
	return (SUCCESS);
}
