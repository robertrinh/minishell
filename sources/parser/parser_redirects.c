/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_redirects.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/21 20:55:56 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/21 16:55:06 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_redirect	*construct_redirect_file(t_token *token, t_shell *shell)
{
	t_redirect	*file;

	file = NULL;
	file = safe_malloc(sizeof(t_redirect), shell);
	if (file == NULL)
		return (NULL);
	if (token->next)
		file->value = token->next->value;
	file->fd = 0;
	file->type = assign_file_type(token->value);
	file->next = NULL;
	return (file);
}

static t_redirect	*append_redirect(t_redirect *files, t_token *current, \
						t_shell *shell)
{
	files->next = construct_redirect_file(current, shell);
	files = files->next;
	return (files);
}

static t_redirect	*redirects_for_type(t_parse *p, t_token_type type, \
						t_shell *shell)
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
				files = construct_redirect_file(current, shell);
				files_head = files;
			}
			else
				files = append_redirect(files, current, shell);
		}
		if (current->type == PIPE)
			break ;
		current = current->next;
	}
	return (files_head);
}

t_cmd	*construct_redirects(t_cmd *cmd, t_parse *p, t_shell *shell)
{
	cmd->fd_in = redirects_for_type(p, REDIR_IN, shell);
	cmd->fd_out = redirects_for_type(p, REDIR_OUT, shell);
	return (cmd);
}
