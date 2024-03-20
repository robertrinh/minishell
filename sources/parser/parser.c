/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 19:53:12 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/20 16:43:25 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmd	*construct_command(t_cmd *cmd, t_parse *p)
{
	if (p->tokens_c->type == COMMAND)
		cmd->value = p->tokens_c->value;
	return (cmd);
}

t_cmd	*build_cmd(t_parse *p)
{
	t_cmd	*cmd;

	p->tokens_c = locate_current_token(p);
	if (p->tokens_c)
	{
		cmd = allocate_cmd();
		cmd = construct_command(cmd, p);
		cmd = construct_args(cmd, p);
		cmd = construct_redirects(cmd, p);
		p->current_pipe++;
		return (cmd);
	}
	return (NULL);
}

bool	build_cmds(t_parse *p)
{
	while (p->i < p->cmd_count)
	{
		p->cmds[p->i] = build_cmd(p);
		p->i++;
	}
	return (SUCCESS);
}

bool	parse(t_shell *shell)
{
	t_cmd	**cmds;
	t_parse	*p;

	should_print("\n\n========parser========\n", shell->print_output);
	p = init_parse(shell);
	if (parser_checks(shell->tokens))
		build_cmds(p);

	shell->cmd_table->cmds = p->cmds;
	shell->cmd_table->cmd_count = p->cmd_count;
	
	free(p);

	parser_post_process(shell);

	if (shell->print_output)
		print_cmds(shell->cmd_table);
	return (SUCCESS);
}

