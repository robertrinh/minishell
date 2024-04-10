/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_open.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 15:04:57 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/04/10 14:45:58 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	safe_open(char *path, t_redirect_type oflag, int mode)
{
	int		fd;

	if (mode == 0)
		mode = 0644;
	fd = STDIN_FILENO;
	fd = open(path, oflag, mode);
	if (fd == -1)
		show_error_message(E_OPENING_FILE, C_RED, path, X_OPENING_FILE);
	return (fd);
}

t_in_files	*open_in_files(t_cmd *cmd, t_in_files *ins, t_redirect_type type)
{
	int			i;
	t_redirect	*in_files;

	i = 0;
	in_files = cmd->fd_in;

	while (in_files)
	{
		if (in_files->type == type && type == IN_APPEND)
		{
			ins->heredocs[i] = setup_heredoc(in_files);
			i++;
		}
		if (in_files->type == type && type == IN)
		{
			ins->infiles[i] = safe_open(in_files->value, get_open_flag_for_type(IN), 0);
			i++;
		}
		if (in_files->next == NULL)
			break ;
		in_files = in_files->next;
	}
	return (ins);
}
