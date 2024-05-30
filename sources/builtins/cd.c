/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 14:31:20 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/05/30 17:29:16 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	minus_flag_check(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (cmd->args[0] == NULL)
		return (true);
	else if (ft_strncmp(cmd->args[0], "-", 2) == 0)
	{
		path = get_value_for_key(shell->envp, "OLDPWD");
		if (path == NULL)
		{
			show_error_message("OLDPWD not set: ", C_RED, cmd->value, 1);
			return (free(path), false);
		}
		ft_putendl_fd(path, STDOUT_FILENO);
		return (free(path), false);
	}
	return (true);
}

static char	*set_home_directory(t_cmd *cmd, t_shell *shell)
{
	char	*home_dir;

	home_dir = get_value_for_key(shell->envp, "HOME");
	if (home_dir == NULL)
	{
		show_error_message("HOME not set: ", C_RED, cmd->value, 1);
		return (NULL);
	}
	return (home_dir);
}

static bool	homedir_check(t_cmd *cmd)
{
	if (cmd->arg_count == 0)
		return (true);
	else if (ft_strncmp(cmd->args[0], "~", 2) == 0)
		return (true);
	return (false);
}

static char	*determine_path(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (homedir_check(cmd) == true)
	{
		path = set_home_directory(cmd, shell);
		return (path);
	}
	path = safe_strdup(cmd->args[0]);
	if (path == NULL)
		return (NULL);
	return (path);
}

int	cd(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (cmd->arg_count > 1)
		return (show_error_message(E_CD, C_RED, "", X_FAILURE));
	if (minus_flag_check(cmd, shell) == false)
		return (0);
	path = determine_path(cmd, shell);
	if (path == NULL)
		return (X_FAILURE);
	if (chdir(path) == -1)
	{
		free(path);
		return (show_error_message(E_NO_FILE_DIR, C_RED, cmd->args[0], 1));
	}
	else
		update_env(shell);
	return (free(path), EXIT_SUCCESS);
}
