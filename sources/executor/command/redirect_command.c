/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_command.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 15:04:57 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/02/23 17:55:28 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//iterate over list, for every item, helper to execute
static t_redirect	*file_type(t_cmd *cmd, t_redirect_type type)
{
	if (type == IN)
		return (cmd->fd_in);
	if (type == OUT)
		return (cmd->fd_out);
	return (NULL);
}

static void	assign_file_for_type(t_cmd *cmd, t_redirect_type type, t_redirect *fd)
{
	if (type == IN)
		cmd->fd_in = fd;
	if (type == OUT)
		cmd->fd_out = fd;
}

void	open_redirects(t_cmd *cmd)
{
	t_redirect	*fd;
	t_redirect	*fd_head;
	int	type;

	type = 0;
	while (type < REDIR_NONE)
	{
		fd = file_type(cmd, type);
		fd_head = fd;
		while (fd)
		{
			// open file / return FD
			fd->fd = open(fd->value, O_RDONLY);
			// printf("fd when opened is %d\n", fd->fd);
			fd = fd->next;
		}
		assign_file_for_type(cmd, type, fd_head);
		type++;
	}
}

// echo hello > README.md > README.md > README.md > README.md 