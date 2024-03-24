/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_post_process.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/16 10:13:21 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/24 13:17:38 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	process_args(char **env, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (i < cmd->arg_count)
	{
		if (contains_quote(cmd->args[i]) == S_QUOTE_CHAR)
			cmd->args[i] = strip_quote_for_type(cmd->args[i], S_QUOTE_CHAR);
		else if (contains_quote(cmd->args[i]) == D_QUOTE_CHAR)
		{
			cmd->args[i] = strip_quote_for_type(cmd->args[i], D_QUOTE_CHAR);
			cmd->args[i] = will_expand(env, cmd->args[i]);
			printf("expanded arg: %s\n", cmd->args[i]);
		}
		else
			cmd->args[i] = will_expand(env, cmd->args[i]);
		i++;
	}
	return (0);
}

int		parser_post_process(t_shell *shell)
{
	int		i;
	char	*cmd_value;

	i = 0;
	while (i < shell->cmd_table->cmd_count)
	{
		// cmd_value = shell->cmd_table->cmds[i]->value;
		// shell->cmd_table->cmds[i]->value = will_expand(shell->envp, cmd_value);
		// strip_quote_chars(shell->cmd_table->cmds[i]->value);
		process_args(shell->envp, shell->cmd_table->cmds[i]);
		i++;
	}
	return (0);
}
