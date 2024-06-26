/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_post_process.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/16 10:13:21 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/27 14:29:36 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmd	*process_args(char **env, t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 0;
	while (i < cmd->arg_count)
	{
		if (contains_quote(cmd->args[i]) == S_QUOTE_CHAR)
			cmd->args[i] = new_strip_quotes(cmd->args[i]);
		else if (contains_quote(cmd->args[i]) == D_QUOTE_CHAR)
		{
			cmd->args[i] = will_expand(env, cmd->args[i], shell);
			cmd->args[i] = new_strip_quotes(cmd->args[i]);
		}
		else
			cmd->args[i] = will_expand(env, cmd->args[i], shell);
		i++;
	}
	return (cmd);
}

static t_cmd	*process_cmd(char **env, t_cmd *cmd, t_shell *shell)
{
	if (cmd->value == NULL)
		return (cmd);
	if (contains_quote(cmd->value) == S_QUOTE_CHAR)
	{
		cmd->value = will_expand(env, cmd->value, shell);
		cmd->value = new_strip_quotes(cmd->value);
	}
	else if (contains_quote(cmd->value) == D_QUOTE_CHAR)
	{
		cmd->value = will_expand(env, cmd->value, shell);
		cmd->value = new_strip_quotes(cmd->value);
	}
	return (cmd);
}

int	parser_post_process(t_shell *shell)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = shell->cmd_table->cmds[i];
	while (i < shell->cmd_table->cmd_count)
	{
		cmd = process_cmd(shell->envp, cmd, shell);
		cmd = process_args(shell->envp, cmd, shell);
		i++;
	}
	return (0);
}
