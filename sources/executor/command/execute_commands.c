/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_commands.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 15:22:01 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/02/25 13:06:32 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	execute_command(t_shell *shell, int i)
{
	char	*cmd_path;
	char	**formatted_cmd;

	cmd_path = shell->cmd_table->cmds[i]->cmd_path;
	formatted_cmd = shell->cmd_table->cmds[i]->formatted_cmd;

	execve(cmd_path, formatted_cmd, shell->envp);

	return (SUCCESS);
}

int	execute_commands(t_shell *shell)
{
    int i;
	t_pipes	*pipes;

	i = 0;
	pipes = init_pipes();
    while (i < shell->cmd_table->cmd_count) 
	{
        prepare_command(shell, i);
		open_in_redirects(shell->cmd_table->cmds[i]);
		will_open_pipe(shell->cmd_table, pipes, i);
        new_process(shell, i, pipes);
		iterate_pipes(pipes);
		i++;
    }
    // Close the last pipe ends
	will_close_pipes(pipes);
    return (SUCCESS);
}
