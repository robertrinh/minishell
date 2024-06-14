/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_in_files.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/24 22:08:44 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/14 16:14:24 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_in_files	*init_infiles(t_cmd *cmd)
{
	t_in_files	*ins;

	ins = safe_malloc(sizeof(t_in_files));
	ins->heredocs = safe_malloc(sizeof(int *) * count_files(cmd, IN_APPEND));
	ins->infiles = safe_malloc(sizeof(int *) * count_files(cmd, IN));
	return (ins);
}

static void	close_in_files(t_cmd *cmd, t_in_files *fds, t_redirect_type type)
{
	int		count;

	count = count_files(cmd, type);
	while (count - 1 >= 0)
	{
		if (type == IN_APPEND)
		{
			if (close_fds(fds->heredocs[count - 1], -1, -1) == false)
				show_error_message(E_CLOSE, C_RED, ": IN_APPEND", X_FAILURE);
		}
		if (type == IN)
		{
			if (close_fds(fds->infiles[count - 1], -1, -1) == false)
				show_error_message(E_CLOSE, C_RED, ": IN", X_FAILURE);
		}
		count--;
	}
}

static void	dup_for_fd(int fd)
{
	int	dev_null_fd;

	if (fd < 0)
	{
		dev_null_fd = open("/dev/null", get_open_flag(OUT));
		if (dev_null_fd >= 0)
		{
			if (dup2(dev_null_fd, STDIN_FILENO) < 0)
			{
				show_error_message(E_DUP, C_RED, "dup2 dev_null_fd", X_FAILURE);
				if (close_fds(dev_null_fd, -1, -1) == false)
					show_error_message(E_CLOSE, C_RED, "dup for fd", X_FAILURE);
			}
			if (close_fds(dev_null_fd, -1, -1) == false)
				show_error_message(E_CLOSE, C_RED, "dup for fd", X_FAILURE);
		}
	}
	else
		if (dup2(fd, STDIN_FILENO) < 0)
			show_error_message(E_DUP, C_RED, "", X_FAILURE);
}

static void	dup_infile(t_cmd *cmd, t_in_files *ins, t_redirect_type type)
{
	int	index;

	index = count_files(cmd, type) - 1;
	if (index >= 0)
	{
		if (type == IN_APPEND)
			dup_for_fd(ins->heredocs[index]);
		else if (type == IN)
			dup_for_fd(ins->infiles[index]);
	}
}

t_validation	redirect_in_files(t_cmd *cmd, int *stat_loc)
{
	t_redirect_type		last_type;
	t_in_files			*ins;

	ins = init_infiles(cmd);
	last_type = last_infile_type(cmd);
	ins = open_in_files(cmd, ins, IN_APPEND, stat_loc);
	ins = open_in_files(cmd, ins, IN, NULL);
	if (last_type == IN_APPEND)
		dup_infile(cmd, ins, IN_APPEND);
	else if (last_type == IN)
		dup_infile(cmd, ins, IN);
	close_in_files(cmd, ins, IN_APPEND);
	close_in_files(cmd, ins, IN);
	free_ins(ins);
	return (SUCCESS);
}
