/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_in_files.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/24 22:08:44 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/02/24 22:09:34 by quentinbeuk   ########   odam.nl         */
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

void	redirect_in_files(t_cmd *cmd, int *fd_ins)
{
	int		i;
	int		count;
	char	*buff;
	size_t	read_bytes;
	int		temp_pipe[2];

	i = 0;
	count = count_redirects_for_type(cmd, IN);
	pipe(temp_pipe);
	buff = malloc(sizeof(char *) * BUFF_SIZE);
	while (i < count)
	{
		if (fd_ins[i] != STDIN_FILENO)
		{
			read_bytes = read_large_file(fd_ins[i], &buff);
			write(temp_pipe[WRITE], buff, read_bytes);
		}
		i++;
	}
	dup2(temp_pipe[READ], STDIN_FILENO);
	close(temp_pipe[READ]);
	close(temp_pipe[WRITE]);
}
