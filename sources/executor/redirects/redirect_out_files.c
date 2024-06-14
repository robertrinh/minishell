/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out_files.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:35:51 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/06/14 14:35:11 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_validation	close_out_files(t_cmd *cmd)
{
	t_validation	validation;
	t_redirect		*fd_curr;

	validation = SUCCESS;
	fd_curr = cmd->fd_out;
	while (fd_curr)
	{
		if (fd_curr->fd == -1)
			validation = FAILURE;
		if (close_fds(fd_curr->fd, -1, -1) == false)
			show_error_message(E_CLOSE, C_RED, "fd_out", X_FAILURE);
		fd_curr = fd_curr->next;
	}
	return (validation);
}

/*
	Returnes fd of the last opened file
*/
static int	open_out_files(t_cmd *cmd)
{
	t_redirect	*fd_lst_head;
	t_redirect	*fd_lst_last;
	t_redirect	*curr;

	fd_lst_head = cmd->fd_out;
	curr = cmd->fd_out;
	while (curr)
	{
		curr->fd = safe_open(curr->value, get_open_flag(curr->type), 0644);
		if (curr->fd == -1)
			break ;
		if (curr->next == NULL)
			break ;
		curr = curr->next;
	}
	fd_lst_last = curr;
	cmd->fd_out = fd_lst_head;
	return (fd_lst_last->fd);
}

t_validation	redirect_out(t_cmd *cmd)
{
	int		fd;
	int		dev_null_fd;

	fd = open_out_files(cmd);
	if (fd > 0)
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
			show_error_message(E_DUP, C_RED, "", X_FAILURE);
	}
	else
	{
		dev_null_fd = open("/dev/null", get_open_flag(OUT));
		if (dev_null_fd >= 0)
		{
			if (dup2(dev_null_fd, STDOUT_FILENO) < 0)
				show_error_message(E_DUP, C_RED, "", X_FAILURE);
			cmd->fd_out->fd = dev_null_fd;
		}
	}
	return (close_out_files(cmd));
}
