/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/08 15:54:04 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/02/23 18:02:21 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_pipes	*init_pipes(void)
{
	t_pipes	*pipes;

	pipes = malloc(sizeof(t_pipes));
	if (pipes == NULL)
	{
		// TODO protect
	}
	pipes->prev_pipe[0] = -1;
	pipes->prev_pipe[1] = -1;
	pipes->curr_pipe[0] = -1;
	pipes->curr_pipe[1] = -1;
	return (pipes);
}

void	will_open_pipe(t_cmd_table *cmd_table, t_pipes *pipes, int i)
{
	// Only create a pipe if not the last command
    if (i < cmd_table->cmd_count - 1)
        pipe(pipes->curr_pipe);
}

void	will_close_pipes(t_pipes *pipes)
{
    if (pipes->prev_pipe[READ] != -1)
	{
        close(pipes->prev_pipe[READ]);
        close(pipes->prev_pipe[WRITE]);
	}
}

void	dup_fds(t_pipes *pipes, t_cmd *cmd)
{
	int fd_input = STDIN_FILENO;
	
	if (cmd->fd_in)
		fd_input = fd_in_file(cmd);
	
	printf("fd_input is %d\n", fd_input);
	// First
	if (pipes->prev_pipe[READ] != -1)
	{
        close(pipes->prev_pipe[WRITE]);
        dup2(pipes->prev_pipe[READ], fd_input); // was STDIN_FILENO
        close(pipes->prev_pipe[READ]);
    }
	// Not first
	if (pipes->curr_pipe[WRITE] != -1)
	{
		close(pipes->curr_pipe[READ]);
		dup2(pipes->curr_pipe[WRITE], STDOUT_FILENO);
		close(pipes->curr_pipe[WRITE]);
	}
}

void	iterate_pipes(t_pipes *pipes)
{
	 // Update pipes->prev_pipe for the next iteration
    pipes->prev_pipe[READ] = pipes->curr_pipe[READ];
    pipes->prev_pipe[WRITE] = pipes->curr_pipe[WRITE];
}
