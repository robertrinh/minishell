/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_command.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/22 21:21:55 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/04/22 21:35:52 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_validation	execute_command(t_shell *shell, int i)
{
	char	*cmd_value;
	char	*cmd_path;
	char	**formatted_cmd;

	cmd_value = shell->cmd_table->cmds[i]->value;
	cmd_path = shell->cmd_table->cmds[i]->cmd_path;
	formatted_cmd = shell->cmd_table->cmds[i]->formatted_cmd;
	if (execve(cmd_path, formatted_cmd, shell->envp) == -1)
		return (show_error_message(E_CMD, C_RED, cmd_value, X_CMD));
	return (SUCCESS);
}
