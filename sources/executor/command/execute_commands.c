/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_commands.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 15:22:01 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/04/18 14:13:00 by robertrinh    ########   odam.nl         */
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

int	execute_commands(t_shell *shell)
{
	int			i;
	t_pipes		*pipes;
	char		*cmd_value;

	i = 0;
	pipes = init_pipes();
	while (i < shell->cmd_table->cmd_count)
	{
		prepare_command(shell, i);
		if (shell->cmd_table->cmds[i]->cmd_path == NULL)
		{
			cmd_value = shell->cmd_table->cmds[i]->value;
			show_error_message(E_CMD_NOT_FOUND, C_RED, cmd_value, X_CMD);
			return (g_exit_code);
		}
		if (shell->cmd_table->cmds[i]->fd_in)
			redirect_in_files(shell->cmd_table->cmds[i]);
		will_open_pipe(shell->cmd_table, pipes, i);
		new_process(shell, i, pipes, shell->cmd_table->cmds[i]);
		iterate_pipes(pipes);
		i++;
	}
	will_close_pipes(pipes);
	return (g_exit_code);
}
