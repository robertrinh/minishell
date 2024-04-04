/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_commands.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 15:22:01 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/04/04 17:46:13 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	execute_command(t_shell *shell, int i)
{
	char	*cmd_path;
	char	**formatted_cmd;

	cmd_path = shell->cmd_table->cmds[i]->cmd_path;
	formatted_cmd = shell->cmd_table->cmds[i]->formatted_cmd;

	execve(cmd_path, formatted_cmd, shell->envp); // TODO protec
}



int	execute_commands(t_shell *shell)
{
    int	i;
	// int	exit_status;
	t_pipes	*pipes;
	
	i = 0;
	pipes = init_pipes();
    while (i < shell->cmd_table->cmd_count) 
	{
        prepare_command(shell, i);
		if (shell->cmd_table->cmds[i]->fd_in)
			redirect_in_files(shell->cmd_table->cmds[i]);
		will_open_pipe(shell->cmd_table, pipes, i);
        new_process(shell, i, pipes);
		iterate_pipes(pipes);
		i++;
    }
	will_close_pipes(pipes);
    return (SUCCESS);
}
