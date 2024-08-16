/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_should_patch.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/16 15:13:25 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/08/16 16:29:55 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	patch_args(t_shell *shell, t_cmd *cmd)
{
	int		i;
	int		j;
	char	**new_args;

	i = 0;
	j = 0;
	if (cmd->arg_count < 1)
		return (show_error(E_CMD_NOT_FOUND, shell, "PATH_ARG", X_FAILURE));
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
	Returns a copy of the first arg
	!! Uses dup
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
		return (show_error(E_CMD_NOT_FOUND, shell, "PATCH_CMD", EXIT_FAILURE));
	else
		cmd->value = cmd_value;
	return (SUCCESS);
}

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
