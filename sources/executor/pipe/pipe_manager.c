/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_manager.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/29 13:17:01 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/03/02 11:27:38 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

void	dup_fds(t_pipes *pipes, t_cmd *cmd)
{
	int 	*fd_ins;
	int		*fd_heredocs;

	if (cmd->heredoc)
		fd_heredocs = collect_heredocs(cmd);
	if (cmd->fd_in)
		fd_ins = collect_fd_in_files(cmd);
	if (cmd->fd_in || cmd->heredoc)
		redirect_in_files(cmd, fd_ins, fd_heredocs);
	if (pipes->prev_pipe[READ] != -1)
	{
        close(pipes->prev_pipe[WRITE]);
        dup2(pipes->prev_pipe[READ], STDIN_FILENO);
        close(pipes->prev_pipe[READ]);
    }
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
