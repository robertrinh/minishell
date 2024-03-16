/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_post_process.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/16 10:13:21 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/16 11:18:52 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	process_cmd(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (i < cmd->arg_count)
	{
		if (cmd->args[i][0] == D_QUOTE_CHAR)
		{
			strip_quote_chars(cmd->args[i]);
			will_expand_quotes(cmd->args[i]);
		}
		// TODO Remove single quote characters
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
		process_cmd(cmds[i]);
		i++;
	}
	return (0);
}
