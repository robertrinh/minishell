/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_patch_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:16:26 by quentin           #+#    #+#             */
/*   Updated: 2024/09/02 14:16:32 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	patch_args(t_shell *shell, t_cmd *cmd)
{
	int		i;
	int		j;
	char	**new_args;

	i = 0;
	j = 0;
	if (cmd->arg_count < 1)
		return (SUCCESS);
	new_args = safe_malloc((cmd->arg_count) * sizeof(char *), shell);
	while (i <= cmd->arg_count)
	{
		if (i == 0)
			i++;
		new_args[j] = safe_strdup(cmd->args[i], shell);
		i++;
		j++;
	}
	free_2d_array(cmd->args);
	cmd->args = new_args;
	cmd->arg_count -= 1;
	return (SUCCESS);
}

/*
	Returns a malloced copy of the first arg.
*/
static char	*first_arg(t_shell *shell, t_cmd *cmd)
{
	char	*first_arg;

	first_arg = NULL;
	if (cmd->arg_count > 0 && cmd->args[0])
	{
		first_arg = safe_strdup(cmd->args[0], shell);
		return (first_arg);
	}
	return (NULL);
}

static bool	patch_command(t_shell *shell, t_cmd *cmd)
{
	char	*cmd_value;

	cmd_value = NULL;
	cmd_value = first_arg(shell, cmd);
	if (cmd_value == NULL)
		return (SUCCESS);
	else
		cmd->value = cmd_value;
	return (SUCCESS);
}

/*
	If a command begins with an operator, command value is not set.
	should_patch_command will set the first valit arg to the command value/
*/
bool	should_patch_command(t_shell *shell)
{
	t_cmd	**cmds;
	int		i;

	i = 0;
	cmds = shell->cmd_table->cmds;
	while (i < shell->cmd_table->cmd_count)
	{
		if (cmds[i]->value)
		{
			i++;
			continue ;
		}
		else if (cmds[i]->value == NULL)
			if (patch_command(shell, cmds[i]) == FAILURE)
				return (FAILURE);
		if (patch_args(shell, cmds[i]) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
