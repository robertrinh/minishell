/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 19:43:07 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/08 17:32:31 by qtrinh        ########   odam.nl         */
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
    pid_t pid;

    pid = fork();
	handle_signals(CHILD);
    if (pid == 0) 
	{
		dup_fds(pipes, shell->cmd_table->cmds[i]);
        execute_command(shell, i);
    }
	else if (pid > 0)
	{
		// Close the previous pipe ends if not the first command
		will_close_pipes(pipes);
        waitpid(pid, NULL, 0);
    }
    return (SUCCESS);
}
