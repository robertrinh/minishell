/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 22:22:42 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/21 16:47:01 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmd	**init_cmds(int cmd_count, t_shell *shell)
{
	t_cmd	**cmds;
	int		i;

	i = 0;
	cmds = safe_malloc(sizeof(t_cmd) * (cmd_count + 1), shell);
	while (i < cmd_count)
	{
		cmds[i] = NULL;
		i++;
	}
	return (cmds);
}

t_parse	*init_parse(t_shell *shell)
{
	t_parse	*p;

	p = safe_malloc(sizeof(t_parse), shell);
	p->tokens_r = shell->tokens;
	p->tokens_c = shell->tokens;
	p->current_pipe = 0;
	p->cmd_count = count_pipes(shell) + 1;
	p->cmds = init_cmds(p->cmd_count, shell);
	p->i = 0;
	return (p);
}

t_cmd	*allocate_cmd(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = safe_malloc(sizeof(t_cmd), shell);
	cmd->value = NULL;
	cmd->args = NULL;
	cmd->cmd_and_args = NULL;
	cmd->cmd_path = NULL;
	cmd->fd_in = NULL;
	cmd->fd_out = NULL;
	cmd->arg_count = 0;
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

t_token	*locate_current_token(t_parse *p)
{
	if (p->current_pipe == 0)
		return (p->tokens_r);
	else
		return (p->tokens_c = locate_pipe_n(p->tokens_r, \
				(p->current_pipe - 1))-> next);
}
