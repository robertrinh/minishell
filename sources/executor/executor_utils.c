/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 19:43:07 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/04/23 21:56:49 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	prepare_command(t_shell *shell, int i)
{
	char	**env_paths;
	char	*cmd_path;
	t_cmd	*cmd;

	cmd = shell->cmd_table->cmds[i];
	env_paths = get_paths(shell);
	if (env_paths == NULL)
	{
		cmd->cmd_path = NULL;
		return (FAILURE);
	}
	cmd->formatted_cmd = format_cmd(cmd);
	cmd_path = get_path_for_cmd(env_paths, cmd->value);
	cmd->cmd_path = cmd_path;
	return (SUCCESS);
}
