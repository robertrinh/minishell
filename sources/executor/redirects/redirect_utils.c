/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:07:55 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/02/29 14:01:10 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int		count_redirects_for_type(t_cmd *cmd, t_redirect_type type)
{
	int			count;
	t_redirect	*fd;

	count = 0;
	fd = file_type(cmd, type);
	if (fd == NULL)
		return (count);
	while (fd)
	{
		count++;
		fd = fd->next;
	}
	return (count);
}

size_t read_large_file(int fd, char ***buff)
{
	size_t		read_bytes;
	size_t		buff_size;
	size_t		total_bytes;
	char		*temp;

	buff_size = BUFF_SIZE;
	*buff = safe_malloc(buff_size);
	total_bytes = 0;
    while ((read_bytes = read(fd, *buff + total_bytes, buff_size - total_bytes)) > 0)
	{
		total_bytes += read_bytes;
		if (total_bytes >= buff_size)
		{
			buff_size *= 2;
			temp = ft_realloc(*buff, buff_size);
			*buff = &temp;
		}
	}
	return (total_bytes);
}
