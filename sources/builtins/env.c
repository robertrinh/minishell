/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 14:45:44 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/04/04 17:38:23 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env(t_shell *shell)
{
	int		i;
	char	**envp;

	i = 0;
	envp = shell->envp;
	if (envp == NULL)
		return (1); //!error message no envp found
	while (envp[i])
	{
		ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
	exit(0);
}
// TODO split key and value
