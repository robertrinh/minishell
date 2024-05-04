/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_piped_command.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/22 21:13:57 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/05/02 16:15:17 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_validation	execute_piped_command(t_shell *shell, t_cmd *cmd)
{
	char	*cmd_value;
	char	*cmd_path;
	char	**formatted_cmd;

	cmd_value = cmd->value;
	cmd_path = cmd->cmd_path;
	formatted_cmd = cmd->formatted_cmd;
	if (is_builtin(shell->builtin_child, cmd, B_NUM_CHILD))
		exec_builtin(shell->builtin_child, cmd, shell, B_NUM_CHILD);
	else if (execve(cmd_path, formatted_cmd, shell->envp) == -1)
	{
		show_error_message(E_EXECVE, C_RED, cmd_value, X_EXECVE);
		exit(g_exit_code);
	}
	return (SUCCESS);
}
