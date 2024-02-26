/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_open.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 15:04:57 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/02/24 22:52:17 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int open_file_for_type(char *file_name, t_redirect_type type)
{
	int		fd;

	fd = STDIN_FILENO;
	fd = open(file_name, get_open_flag_for_type(type));
	if (fd == -1)
	{
		// TODO check file permission
		// TODO hanlde error
		return (-1);
	}
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
		fd->fd = open_file_for_type(fd->value, IN);
		fd = fd->next;
	}
	cmd->fd_in = fd_head;
}
