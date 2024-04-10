/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/03 09:41:20 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/04/10 14:41:29 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	arg_error(void)
{
	g_exit_code = EXIT_FAILURE;
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
}

static void	numeric_error(char *str)
{
	g_exit_code = X_NEUMERIC_ERROR;
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

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
	// ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (cmd->arg_count > 1)
		arg_error();
	if (cmd->arg_count == 1)
	{
		if (ft_isnumber(cmd->args[0]) == false || ft_strlen(cmd->args[0]) > 19)
			numeric_error(cmd->args[0]);
		else
			g_exit_code = ft_atoi(cmd->args[0]) % 256;
	}
	exit(g_exit_code);
}
