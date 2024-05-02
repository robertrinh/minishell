/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/03 09:41:20 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/05/02 16:23:12 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

int	exit_shell(t_cmd *cmd, t_shell *shell)
{
	(void) shell;
	if (shell->cmd_table->cmd_count == 1)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (cmd->arg_count > 1)
	{
		arg_error();
		return (EXIT_FAILURE);
	}
	if (cmd->arg_count == 1)
	{
		if (ft_isnumber(cmd->args[0]) == false || ft_strlen(cmd->args[0]) > 19)
			numeric_error(cmd->args[0]);
		else
			g_exit_code = ft_atoi(cmd->args[0]) % 256;
	}
	exit(g_exit_code);
}
