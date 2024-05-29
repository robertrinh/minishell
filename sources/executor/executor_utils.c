/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 19:43:07 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/05/25 21:57:37 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	close_fds(int fd1, int fd2, int fd3)
{
    if (fd1 != -1 && close(fd1) < 0)
		return (FAILURE);
    if (fd2 != -1 && close(fd2) < 0)
		return (FAILURE);
    if (fd3 != -1 && close(fd3) < 0)
		return (FAILURE);
    return (SUCCESS);
}

static bool	absolute_check(t_cmd *cmd)
{
	if (access(cmd->value, X_OK | F_OK) == 0)
	{
		cmd->cmd_path = safe_strdup(cmd->value);
		cmd->cmd_and_args = format_cmd(cmd);
		return (SUCCESS);
	}
	return (FAILURE);
}

int	prepare_command(t_shell *shell, int i)
{
	char	**env_paths;
	char	*cmd_path;
	t_cmd	*cmd;

	cmd = shell->cmd_table->cmds[i];
	if (absolute_check(cmd) == SUCCESS)
		return (SUCCESS);
	env_paths = get_paths(shell);
	if (env_paths == NULL)
	{
		cmd->cmd_path = NULL;
		return (FAILURE);
	}
	cmd->cmd_and_args = format_cmd(cmd);
	cmd_path = get_path_for_cmd(env_paths, cmd->value);
	free_2d_array(env_paths);
	if (cmd_path == NULL)
	{
		cmd->cmd_path = NULL;
		return (FAILURE);
	}
	cmd->cmd_path = safe_strdup(cmd_path);
	free (cmd_path); //! < Move to shell free
	return (SUCCESS);
}
