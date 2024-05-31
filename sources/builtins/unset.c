/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 21:02:51 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/05/31 13:06:49 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	remove_line_from_env(char **env, const char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0 &&
			env[i][len] == '=')
		{
			free(env[i]);
			while (env[i + 1])
			{
				env[i] = env[i + 1];
				i++;
			}
			env[i] = NULL;
			return ;
		}
		i++;
	}
}

int	unset(t_cmd* cmd, t_shell *shell)
{
	int	i;

	i = 0;
	while (i < cmd->arg_count)
	{
		remove_line_from_env(shell->envp, cmd->args[i]);
		i++;
	}
	return (0);
}
