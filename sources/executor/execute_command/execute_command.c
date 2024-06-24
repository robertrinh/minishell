/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_command.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/22 21:21:55 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/21 17:12:51 by qtrinh        ########   odam.nl         */
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
	if (cmd_path == NULL)
		exit(shell->exit_code);
	if (execve(cmd_path, cmd_and_args, shell->envp) == -1)
	{
		show_error_message(E_EXECVE, shell, cmd_value, X_FAILURE);
		exit(shell->exit_code);
		return (FAILURE);
	}
	return (SUCCESS);
}
