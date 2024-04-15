/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 19:43:07 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/04/14 14:20:45 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	prepare_command(t_shell *shell, int i)
{
	char	**env_paths;
	char	*cmd_path;
	t_cmd	*cmd;

	cmd = shell->cmd_table->cmds[i];
	env_paths = get_paths(shell);
	if (env_paths == NULL)
	{
		cmd->cmd_path = NULL;
		return (FAILURE);
	}
	cmd->formatted_cmd = format_cmd(cmd);
	cmd_path = get_path_for_cmd(env_paths, cmd->value);
	cmd->cmd_path = cmd_path;
	return (SUCCESS);
}

int	new_process(t_shell *shell, int i, t_pipes *pipes, t_cmd *cmd)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		// TODO fork error
	}
	if (pid == 0)
	{
		handle_signals(CHILD);
		if (dup_fds(pipes, shell->cmd_table->cmds[i]) == SUCCESS)
		{
			if (is_builtin(shell->builtin_child, cmd, B_NUM_CHILD))
				exec_builtin(shell->builtin_child, cmd, shell, B_NUM_CHILD);
			if (execute_command(shell, i) == FAILURE)
			{
				will_close_pipes(pipes);
				exit(X_CMD);
			}
		}
	}
	else if (pid > 0)
	{
		will_close_pipes(pipes);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
	}
	return (g_exit_code);
}
