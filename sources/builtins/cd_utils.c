/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/30 16:09:22 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/05/30 17:27:30 by qtrinh        ########   odam.nl         */
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
		shell->envp[j] = safe_strjoin("PWD=", buff);
	}
}

static void	update_oldpwd(t_shell *shell)
{
	int		i;
	char	*pwd;

	i = index_for_env_key(shell->envp, "OLDPWD");
	pwd = get_value_for_key(shell->envp, "PWD");
	if (pwd == NULL)
		return (free(pwd));
	if (i != -1)
	{
		free(shell->envp[i]);
		shell->envp[i] = safe_strjoin("OLDPWD=", pwd);
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
	oldpwd = get_value_for_key(shell->envp, "OLDPWD");
	if (oldpwd != NULL)
		update_oldpwd(shell);
	pwd = get_value_for_key(shell->envp, "PWD");
	if (pwd != NULL)
		update_pwd(shell, buff);
	free(oldpwd);
	free(pwd);
	free(buff);
}
