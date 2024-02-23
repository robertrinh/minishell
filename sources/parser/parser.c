/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 19:53:12 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/02/23 15:48:34 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ====================================================: CMD + Args

t_cmd	*construct_command(t_cmd *cmd, t_parse *p)
{
	if (p->tokens_c->type == COMMAND)
		cmd->value = p->tokens_c->value;
	return (cmd);
}

int	count_args(t_parse *p)
{
	int			count;
	t_token		*current_token;

	count = 0;
	current_token = p->tokens_c;
	while (current_token)
	{
		if (current_token->type == PIPE)
			return (count);
		if (current_token->type == ARGUMENT)
			count++;
		current_token = current_token->next;
	}
	return (count);
}

char	**allocate_args(t_parse *p)
{
	char	**args;

	args = malloc(sizeof(char *) * (count_args(p) + 1));
	if (args == NULL)
	{
		// TODO clean_exit()
	}
	return (args);
}

// test this < and that < with | more at the end
t_cmd	*construct_args(t_cmd *cmd, t_parse *p)
{
	int			i;
	t_token		*current;

	i = 0;
	current = p->tokens_c;
	cmd->args = allocate_args(p);
	while (current)
	{
		if (current->type == ARGUMENT)
		{
			cmd->args[i] = ft_strdup(current->value);
			i++;
		}
		if (current->type == PIPE)
			break ;
		current = current->next;
	}
	cmd->arg_count = i;
	return (cmd);
}

// ====================================================: Helpers
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

	printf("\n\n========parser========\n");
	p = init_parse(shell);
	if (parser_checks(shell->tokens))
		build_cmds(p);

	shell->cmd_table->cmds = p->cmds;
	shell->cmd_table->cmd_count = p->cmd_count;
	free(p);

	print_cmds(shell->cmd_table);
	return (SUCCESS);
}

