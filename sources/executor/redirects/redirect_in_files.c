/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_in_files.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/24 22:08:44 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/28 17:05:33 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	*collect_fd_in_files(t_cmd *cmd)
{
	int			i;
	int			*fd_ins;
	t_redirect	*curr_fd;

	i = 0;
	curr_fd = cmd->fd_in;
	
	if (curr_fd == NULL)
		return (NULL);

	while (curr_fd)
	{
		fd_ins[i] = curr_fd->fd;
		i++;
		curr_fd = curr_fd->next;
	}
	return (fd_ins);
}

void	buffer_in_files(t_cmd *cmd, int fd, int *fds, char **buff)
{
	int		i;
	int		count;
	size_t	read_bytes;

	i = 0;
	count = count_redirects_for_type(cmd, IN);
	while (i < count)
	{
		if (fds[i] != STDIN_FILENO)
		{
			read_bytes = read_large_file(fds[i], &buff);
			write(fd, buff, read_bytes);
		}
		i++;
	}
}

void	buffer_heredoc_files(t_cmd *cmd, int fd, int *fds, char **buff)
{
	int		i;
	int		count;
	size_t	read_bytes;

	i = 0;
	count = count_redirects_for_type(cmd, IN_APPEND);
	while (i < count)
	{
		if (fds[i] != STDIN_FILENO)
		{
			read_bytes = read_large_file(fds[i], &buff);
			write(fd, buff, read_bytes);
		}
		i++;
	}
}

void	redirect_in_files(t_cmd *cmd, int *fd_ins, int *fd_heredocs)
{
	char	*buff;
	int		temp_pipe[2];

	pipe(temp_pipe); // TODO protect pipe
	buff = safe_malloc(sizeof(char *) * BUFF_SIZE);

	if (cmd->fd_in)
	{
		buffer_in_files(cmd, temp_pipe[WRITE], fd_ins, &buff);
		write(temp_pipe[WRITE], "\n", 1);
	}
	// if (cmd->heredoc)
	// 	buffer_heredoc_files(cmd, temp_pipe[WRITE], fd_heredocs, &buff);

	dup2(temp_pipe[READ], STDIN_FILENO);
	close(temp_pipe[READ]);
	close(temp_pipe[WRITE]);
}
