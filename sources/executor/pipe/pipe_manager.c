/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_manager.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/29 13:17:01 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/03/28 12:31:08 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	safe_open(const char *path, t_redirect_type oflag, int mode)
{
	int		fd;

	fd = open(path, oflag, mode);
	if (fd == -1)
		show_error_message(ERROR_OPENING_FILE, RED);
	return (fd);
}

void redirect_out(t_cmd *cmd)
{
	int			fd;
	t_redirect	*fd_outs;

	fd_outs = cmd->fd_out;
	while (fd_outs)
	{
		// TODO if permission denied, show_error_message()
		fd_outs->fd = safe_open(fd_outs->value, get_open_flag_for_type(fd_outs->type), 0644);
		if (fd_outs->fd == -1)
			return ;
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
