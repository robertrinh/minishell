/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 19:53:12 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/08/16 15:21:13 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmd	*construct_command(t_cmd *cmd, t_parse *p, t_shell *shell)
{
	if (p->tokens_c->type == COMMAND)
		cmd->value = safe_strdup(p->tokens_c->value, shell);
	else if (p->tokens_c->type == S_QUOTE || p->tokens_c->type == D_QUOTE)
	{
		cmd->value = safe_strdup(p->tokens_c->value, shell);
		if (p->tokens_c->next)
			p->tokens_c = p->tokens_c->next;
	}
	return (cmd);
}

t_cmd	*build_cmd(t_parse *p, t_shell *shell)
{
	t_cmd	*cmd;

	p->tokens_c = locate_current_token(p);
	if (p->tokens_c)
	{
		cmd = allocate_cmd(shell);
		cmd = construct_command(cmd, p, shell);
		cmd = construct_args(cmd, p, shell);
		cmd = construct_redirects(cmd, p, shell);
		p->current_pipe++;
		return (cmd);
	}
	return (NULL);
}

bool	build_cmds(t_parse *p, t_shell *shell)
{
	while (p->i < p->cmd_count)
	{
		p->cmds[p->i] = build_cmd(p, shell);
		p->i++;
	}
	return (SUCCESS);
}

bool	shell_parser(t_shell *shell)
{
	t_parse	*p;

	should_print("\n\n========parser========\n", shell->print_output);
	if (parser_checks(shell) == FAILURE)
		return (FAILURE);
	p = init_parse(shell);
	build_cmds(p, shell);
	shell->cmd_table->cmds = p->cmds;
	shell->cmd_table->cmd_count = p->cmd_count;
	parser_post_process(shell);
	p->cmds = NULL;
	free(p);
	if (shell->print_output)
		print_cmds(shell->cmd_table);
	return (SUCCESS);
}
