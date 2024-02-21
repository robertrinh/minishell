/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 22:22:42 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/02/21 21:34:12 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmd	**init_cmds(int cmd_count)
{
	t_cmd 	**cmds;

	cmds = malloc(sizeof(t_cmd) * (cmd_count + 1));
	if (cmds == NULL)
	{
		// TODO clean_exit()
	}
	return (cmds);
}

t_parse		*init_parse(t_shell *shell)
{
	t_parse		*p;

	p = malloc(sizeof(t_parse));
	if (p == NULL)
	{
		// TODO clean_exit()
	}
	p->tokens_r = shell->tokens;
	p->tokens_c = shell->tokens;
	p->current_pipe = 0;
	p->cmd_count = count_pipes(shell) + 1;
	p->cmds = init_cmds(p->cmd_count);
	p->i = 0;
	return (p);
}

t_cmd	*allocate_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
	{
		// TODO clean_exit()
	}
	return (cmd);
}

t_token	*locate_pipe_n(t_token *tokens_root, int pipe_count)
{
	int			i;
	t_token		*current;

	i = 0;
	current = tokens_root;
	while (current)
	{
		if (current->type == PIPE)
		{
			if (i == pipe_count)
				return (current);
			i++;
		}
		if (current->next == NULL)
			return (NULL);
		current = current->next;
	}
	return (NULL);
}

t_token *locate_current_token(t_parse *p)
{
	if (p->current_pipe == 0)
		return (p->tokens_r);
	else
		return (p->tokens_c = locate_pipe_n(p->tokens_r, (p->current_pipe - 1))-> next);
}
