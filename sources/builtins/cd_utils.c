/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/30 16:09:22 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/08/01 17:50:23 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_pwd(t_shell *shell, char *buff)
{
	int	j;

	j = index_for_env_key(shell->envp, "PWD");
	if (j != -1)
	{
		free(shell->envp[j]);
		shell->envp[j] = safe_strjoin("PWD=", buff, shell);
	}
}

static void	update_oldpwd(t_shell *shell)
{
	int		i;
	char	*pwd;

	i = index_for_env_key(shell->envp, "OLDPWD");
	pwd = get_value_for_key(shell->envp, "PWD", shell);
	if (pwd == NULL)
		return (free(pwd));
	if (i != -1)
	{
		free(shell->envp[i]);
		shell->envp[i] = safe_strjoin("OLDPWD=", pwd, shell);
		free(pwd);
	}
	else
		free(pwd);
}

void	update_env(t_shell *shell)
{
	char	*oldpwd;
	char	*pwd;
	char	*buff;

	buff = getcwd(NULL, 0);
	oldpwd = get_value_for_key(shell->envp, "OLDPWD", shell);
	if (oldpwd != NULL)
		update_oldpwd(shell);
	pwd = get_value_for_key(shell->envp, "PWD", shell);
	if (pwd != NULL)
		update_pwd(shell, buff);
	free(oldpwd);
	free(pwd);
	free(buff);
}

void	cd_error(char *path, t_cmd *cmd, t_shell *shell)
{
	if (access(path, F_OK && X_OK) == -1)
		show_error(E_NO_FILE_DIR, shell, cmd->args[0], X_FAILURE);
	else if (access(path, R_OK) == -1)
		show_error(E_DENY, shell, cmd->args[0], X_FAILURE);
	else
		show_error(E_NOT_A_DIR, shell, cmd->args[0], X_FAILURE);
}
