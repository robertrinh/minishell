/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 21:19:19 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/13 23:11:59 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	index_for_env_key(t_shell *shell, char *key)
{
	int		i;
	char	**env;

	i = 0;
	env = shell->envp;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, ft_strlen(key)) == 0)
		{
			if (env[i][ft_strlen(key)] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}
