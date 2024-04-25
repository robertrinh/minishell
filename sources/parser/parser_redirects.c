/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_redirects.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/21 20:55:56 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/04/25 16:29:49 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_redirect_type assign_file_type(char *value)
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

static t_redirect	*construct_redirect_file(t_token *token)
{
	t_redirect	*file;

	file = safe_malloc(sizeof(t_redirect));
	if (token->next)
		file->value = token->next->value;
	file->fd = 0;
	file->type = assign_file_type(token->value);
	file->next = NULL;
	return (file);
}

static t_redirect	*construct_redirect_files(t_redirect *files, t_token *current)
{
	files->next = construct_redirect_file(current);
	files = files->next;
	return (files);
}

static bool		should_add_files(t_token_type current_type, t_token_type type)
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

static t_redirect	*redirects_for_type(t_parse *p, t_token_type type)
{
	t_redirect	*files;
	t_redirect	*files_head;
	t_token		*current;

	files = NULL;
	files_head = NULL;
	current = p->tokens_c;
	while (current)
	{
		if (should_add_files(current->type, type))
		{
			if (files == NULL)
			{
				files = construct_redirect_file(current);
				files_head = files;
			}
			else
				files = construct_redirect_files(files, current);
		}
		if (current->type == PIPE)
			break ;
		current = current->next;
	}
	// TODO free redirect struct
	return (files_head);
}

t_cmd	*construct_redirects(t_cmd *cmd, t_parse *p)
{
	cmd->fd_in = redirects_for_type(p, REDIR_IN);
	cmd->fd_out = redirects_for_type(p, REDIR_OUT);
	return (cmd);
}
