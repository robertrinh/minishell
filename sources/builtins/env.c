/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 14:45:44 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/04/10 14:30:19 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env(t_cmd *cmd, t_shell *shell)
{
	int		i;

	i = 0;
	if (shell->envp == NULL)
		return (show_error_message(E_ENV_NOT_FOUND, C_RED, "", X_EXPORT));
	while (shell->envp[i])
	{
		ft_putendl_fd(shell->envp[i], STDOUT_FILENO);
		i++;
	}
	return (SUCCESS);
}
