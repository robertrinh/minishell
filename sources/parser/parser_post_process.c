/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_post_process.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/16 10:13:21 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/17 16:40:57 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	strip_quote_chars(char *arg)
{
	int i;
	int	len;

	i = 0;
	len = ft_strlen(arg);
	while (i < len)
	{
		arg[i] = arg[i + 1];
		i++;
	}
	arg[len - 2] = '\0';
}

static int	process_cmd(char **env, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (i < cmd->arg_count)
	{
		if (cmd->args[i][0] == S_QUOTE_CHAR)
			strip_quote_chars(cmd->args[i]);
		else if (cmd->args[i][0] == D_QUOTE_CHAR)
		{
			cmd->args[i] = will_expand(env, cmd->args[i]);
			strip_quote_chars(cmd->args[i]);
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

	i = 0;
	while (i < shell->cmd_table->cmd_count)
	{
		// TODO expand command itself
		process_cmd(shell->envp, shell->cmd_table->cmds[i]);
		i++;
	}
	return (0);
}
