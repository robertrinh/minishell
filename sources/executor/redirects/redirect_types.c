/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_types.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/24 13:08:29 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/02/24 23:35:03 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_redirect	*file_type(t_cmd *cmd, t_redirect_type type)
{
	if (cmd)
	{
		if (type == IN)
			return (cmd->fd_in);
		if (type == OUT)
			return (cmd->fd_out);
	}
	return (NULL);
}

int		get_open_flag_for_type(t_redirect_type type)
{
	if (type == IN)
		return (O_RDONLY);
	if (type == OUT)
		return (O_RDWR | O_CREAT | O_TRUNC);
	if (type == OUT_APPEND)
		return (O_RDWR | O_CREAT | O_APPEND);
	return (-1);
}
