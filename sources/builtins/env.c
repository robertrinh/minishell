/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 14:45:44 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/04/18 14:16:08 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env(t_cmd *cmd, t_shell *shell)
{
	int		i;

	(void)shell;
	(void)cmd;
	i = 0;
	if (shell->envp == NULL)
		return (FAILURE);
	while (shell->envp[i])
	{
		ft_putendl_fd(shell->envp[i], STDOUT_FILENO);
		i++;
	}
	exit(0);
}
