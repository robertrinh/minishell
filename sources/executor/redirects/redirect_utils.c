/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/24 13:07:55 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/05/15 17:35:38 by qtrinh        ########   odam.nl         */
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

int	count_files_for_type(t_cmd *cmd, t_redirect_type type)
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

size_t	read_large_file(int fd, char ***buff)
{
	size_t		read_bytes;
	size_t		buff_size;
	size_t		total_bytes;
	char		*temp;

	buff_size = BUFF_SIZE;
	*buff = safe_malloc(buff_size);
	total_bytes = 0;
	while ((read_bytes = read(fd, *buff + total_bytes, buff_size - total_bytes)) > 0) // ! norm not allowed
	{
		total_bytes += read_bytes;
		if (total_bytes >= buff_size)
		{
			buff_size *= 2;
			temp = ft_realloc(*buff, buff_size);
			*buff = &temp;
		}
	}
	// TODO error handle when read fails?
	// TODO free *buff
	return (total_bytes);
}
