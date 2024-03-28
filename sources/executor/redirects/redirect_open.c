/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_open.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 15:04:57 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/03/28 15:22:04 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	safe_open(const char *path, t_redirect_type oflag, int mode)
{
	int		fd;

	if (mode == 0)
		mode = 0644;
	fd = STDIN_FILENO;
	fd = open(path, oflag, mode);
	if (fd == -1)
		show_error_message(ERROR_OPENING_FILE, RED, path);
	return (fd);
}

void	open_in_redirects(t_cmd *cmd)
{
	t_redirect	*fd;
	t_redirect	*fd_head;

	fd = cmd->fd_in;
	fd_head = cmd->fd_in;
	while (fd)
	{
		fd->fd = safe_open(fd->value, IN, 0);
		fd = fd->next;
	}
	cmd->fd_in = fd_head;
}
