/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_redirects_utils.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/13 16:32:18 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/06/13 16:42:27 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redirect_type	assign_file_type(char *value)
{
	if (ft_strncmp(value, ">", 2) == 0)
		return (OUT);
	else if (ft_strncmp(value, ">>", 2) == 0)
		return (OUT_APPEND);
	else if (ft_strncmp(value, "<", 2) == 0)
		return (IN);
	else if (ft_strncmp(value, "<<", 2) == 0)
		return (IN_APPEND);
	return (REDIR_NONE);
}

bool	should_add_files(t_token_type current_type, t_token_type type)
{
	if (current_type == REDIR_OUT && type == REDIR_OUT)
		return (true);
	else if (current_type == REDIR_IN || current_type == REDIR_IN_APPEND)
	{
		if (type == REDIR_IN)
			return (true);
	}
	return (false);
}
