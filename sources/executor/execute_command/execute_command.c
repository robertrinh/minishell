/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_command.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/22 21:21:55 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/05/25 15:18:09 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_validation	execute_command(t_shell *shell, int i)
{
	char	*cmd_value;
	char	*cmd_path;
	char	**cmd_and_args;

	cmd_value = shell->cmd_table->cmds[i]->value;
	cmd_path = shell->cmd_table->cmds[i]->cmd_path;
	cmd_and_args = shell->cmd_table->cmds[i]->cmd_and_args;
	if (execve(cmd_path, cmd_and_args, shell->envp) == -1)
	{
		show_error_message(E_EXECVE, C_RED, cmd_value, X_FAILURE);
		// ! exit(g_exit_code);
		return (FAILURE);
	}
	return (SUCCESS);
}
