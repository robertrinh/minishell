/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_redirect.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 17:07:25 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/02/23 17:53:46 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	fd_in_file(t_cmd *cmd)
{
	t_redirect *curr_fd;

	curr_fd = cmd->fd_in;
	while (curr_fd)
	{
		if (curr_fd->next == NULL)
			break ;
		curr_fd = curr_fd->next;
	}
	return (curr_fd->fd);
}

//cat < README.md | wc