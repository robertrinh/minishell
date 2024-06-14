/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/24 13:07:55 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/13 15:29:39 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_ins(t_in_files *ins)
{
	if (ins->heredocs)
	{
		free(ins->heredocs);
		ins->heredocs = NULL;
	}
	if (ins->infiles)
	{
		free(ins->infiles);
		ins->infiles = NULL;
	}
	free(ins);
}

t_redirect_type	last_infile_type(t_cmd *cmd)
{
	t_redirect			*in_files;
	t_redirect_type		type;

	type = REDIR_NONE;
	in_files = cmd->fd_in;
	while (in_files)
	{
		type = in_files->type;
		in_files = in_files->next;
	}
	return (type);
}

int	count_files(t_cmd *cmd, t_redirect_type type)
{
	int			count;
	t_redirect	*fd;

	count = 0;
	fd = file_type(cmd, type);
	if (fd == NULL)
		return (count);
	while (fd)
	{
		if (fd->type == type)
			count++;
		fd = fd->next;
	}
	return (count);
}
