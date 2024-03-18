/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_post_process.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/16 10:13:21 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/18 17:59:46 by quentinbeuk   ########   odam.nl         */
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

static int	process_args(char **env, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (i < cmd->arg_count)
	{
		if (cmd->args[i][0] == S_QUOTE_CHAR)
			strip_quote_chars(cmd->args[i]);
		else if (cmd->args[i][0] == D_QUOTE_CHAR)
		{
			strip_quote_chars(cmd->args[i]);
			cmd->args[i] = will_expand(env, cmd->args[i]);
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
		cmd_value = shell->cmd_table->cmds[i]->value;
		shell->cmd_table->cmds[i]->value = will_expand(shell->envp, cmd_value);
		// strip_quote_chars(shell->cmd_table->cmds[i]->value);
		process_args(shell->envp, shell->cmd_table->cmds[i]);
		i++;
	}
	return (0);
}
