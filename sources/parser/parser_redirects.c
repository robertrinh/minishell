/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_redirects.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/21 20:55:56 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/02/21 22:05:55 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_list	*construct_redirect_file(t_token *token)
{
	t_list		*files;

	files = malloc(sizeof(t_list));
	if (files == NULL)
	{
		// TODO clean_exit()
	}
	files->content = token->value;
	files->next = NULL;
	return (files);
}

static t_list	*redriects_for_type(t_cmd *cmd, t_parse *p, t_token_type type)
{
	t_list		*files;
	t_token		*current;

	files = NULL;
	current = p->tokens_c;
	while (current)
	{
		if (current->type == type)
		{
			if (files == NULL)
				files = construct_redirect_file(current->next);
			else
				files->next = construct_redirect_file(current->next);
		}
		if (current->type == PIPE)
			break ;
		current = current->next;
	}
	return (files);
}

t_cmd	*construct_redirects(t_cmd *cmd, t_parse *p)
{
	cmd->fd_in = redriects_for_type(cmd, p, REDIR_IN);
	cmd->fd_out = redriects_for_type(cmd, p, REDIR_OUT);
	return (cmd);
}
