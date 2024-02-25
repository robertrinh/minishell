/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_redirects.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/21 20:55:56 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/02/25 13:30:39 by quentinbeuk   ########   odam.nl         */
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

	file = malloc(sizeof(t_redirect));
	if (file == NULL)
	{
		// TODO clean_exit()
	}
	file->value = token->next->value;
	file->fd = 0;
	file->type = assign_file_type(token->value);
	file->next = NULL;
	return (file);
}

// !  test << this << this more | and << more
static t_redirect	*redirects_for_type(t_cmd *cmd, t_parse *p, t_token_type type)
{
	t_redirect	*files;
	t_redirect	*files_head;
	t_token		*current;

	files = NULL;
	files_head = NULL;
	current = p->tokens_c;
	while (current)
	{
		if (current->type == type)
		{
			// TODO sub function
			if (files == NULL)
			{
				files = construct_redirect_file(current);
				files_head = files;
			}
			else
			{
				files->next = construct_redirect_file(current);
				files = files->next;		
			}
		}
		if (current->type == PIPE)
			break ;
		current = current->next;
	}
	return (files_head);
}

t_cmd	*construct_redirects(t_cmd *cmd, t_parse *p)
{
	cmd->fd_in = redirects_for_type(cmd, p, REDIR_IN);
	cmd->fd_out = redirects_for_type(cmd, p, REDIR_OUT);
	cmd->heredoc = redirects_for_type(cmd, p, REDIR_IN_APPEND);
	return (cmd);
}
