/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 19:43:07 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/05/02 15:59:46 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	prepare_command(t_shell *shell, int i)
{
	char	**env_paths;
	char	*cmd_path;
	t_cmd	*cmd;

	cmd = shell->cmd_table->cmds[i];
	if (access(cmd->value, X_OK | F_OK) == 0)
		cmd->cmd_path = safe_strdup(cmd->value);
	else
	{
		env_paths = get_paths(shell);
		if (env_paths == NULL)
		{
			cmd->cmd_path = NULL;
			return (FAILURE);
		}
		cmd->formatted_cmd = format_cmd(cmd);
		cmd_path = get_path_for_cmd(env_paths, cmd->value);
		free_2d_array(env_paths);
		cmd->cmd_path = cmd_path;
	}
	return (SUCCESS);
}
