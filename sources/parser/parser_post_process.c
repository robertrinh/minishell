/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_post_process.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/16 10:13:21 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/17 10:01:54 by quentinbeuk   ########   odam.nl         */
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
		// If single quote dont expand - strip quotes
		// Else expand
		
		if (cmd->args[i][0] == S_QUOTE_CHAR)
		{
			// strip_quote_chars(cmd->args[i]);
		}
		else
			will_expand(env, cmd->args[i]);

		i++;
	}
	return (0);
}

int		parser_post_process(t_shell *shell)
{
	int		i;
	t_cmd	**cmds;

	i = 0;
	cmds = shell->cmd_table->cmds;
	while (i < shell->cmd_table->cmd_count)
	{
		process_cmd(shell->envp, cmds[i]);
		i++;
	}
	return (0);
}
