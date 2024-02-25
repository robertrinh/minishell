/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/08 15:54:04 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/02/25 18:56:01 by quentinbeuk   ########   odam.nl         */
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

void redirect_out(t_cmd *cmd)
{
	int			fd;
	t_redirect	*fd_outs;

	fd_outs = cmd->fd_out;
	while (fd_outs)
	{
		fd_outs->fd = open(fd_outs->value, get_open_flag_for_type(fd_outs->type), 0644);
		dup2(fd_outs->fd, STDOUT_FILENO);
		close(fd_outs->fd);
		if (fd_outs->next == NULL)
			return ;
		fd_outs = fd_outs->next;
	}
}

// !	grep aa < README.md | wc
//		grep aa << EOF < README.md | wc

void	dup_fds(t_pipes *pipes, t_cmd *cmd)
{
	int 	*fd_ins;
	int		*fd_heredocs;

	// Infiles
	if (cmd->heredoc)
		fd_heredocs = collect_heredocs(cmd);
	
	if (cmd->fd_in)
		fd_ins = collect_fd_in_files(cmd);

	if (cmd->fd_in || cmd->heredoc)
		redirect_in_files(cmd, fd_ins, fd_heredocs);
	
	// Not First
	if (pipes->prev_pipe[READ] != -1)
	{
        close(pipes->prev_pipe[WRITE]);
        dup2(pipes->prev_pipe[READ], STDIN_FILENO);
        close(pipes->prev_pipe[READ]);
    }
		
	// First
	if (pipes->curr_pipe[WRITE] != -1)
	{
		close(pipes->curr_pipe[READ]);
		if (cmd->fd_out)
			redirect_out(cmd);
		else
			dup2(pipes->curr_pipe[WRITE], STDOUT_FILENO);
		close(pipes->curr_pipe[WRITE]);
	}
}

void	iterate_pipes(t_pipes *pipes)
{
    pipes->prev_pipe[READ] = pipes->curr_pipe[READ];
    pipes->prev_pipe[WRITE] = pipes->curr_pipe[WRITE];
}
