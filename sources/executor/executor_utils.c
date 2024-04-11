/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 19:43:07 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/04/10 16:58:42 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	prepare_command(t_shell *shell, int i)
{
	char	**env_paths;
	char	*cmd_path;

	env_paths = get_paths(shell);
	shell->cmd_table->cmds[i]->formatted_cmd = format_cmd(shell->cmd_table->cmds[i]);
	cmd_path = get_path_for_cmd(env_paths, shell->cmd_table->cmds[i]->value);
	shell->cmd_table->cmds[i]->cmd_path = cmd_path;
	return (SUCCESS);
}

int	new_process(t_shell *shell, int i, t_pipes *pipes)
{
	int		status;
	pid_t	pid;
	
    pid = fork();
    if (pid == 0) 
	{
		handle_signals(CHILD);
		if (dup_fds(pipes, shell->cmd_table->cmds[i]) == SUCCESS)
		{
        	if (execute_command(shell, i) == FAILURE)
			{
				will_close_pipes(pipes);
				exit (X_CMD);
			}
		}
    }
	else if (pid > 0)
	{
		will_close_pipes(pipes);
        waitpid(pid, &status, 0);
    }
    return (SUCCESS);
}
