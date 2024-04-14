/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 14:45:13 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/04/14 13:38:35 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_echo_flag(t_cmd *cmd)
{
	if (ft_strncmp(cmd->args[0], "-n", ft_strlen(cmd->args[0])) == 0)
		return (true);
	return (false);
}

static int	echo_start_index(bool flag)
{
	if (flag)
		return (1);
	return (0);
}

static void	print_echo(t_cmd *cmd, bool flag)
{
	int	i;

	i = echo_start_index(flag);
	while (i < cmd->arg_count)
	{
		write(STDOUT_FILENO, cmd->args[i], ft_strlen(cmd->args[i]));
		if (cmd->args[i + 1])
			write(1, " ", 2);
		i++;
	}
	if (flag == false)
		write(1, "\n", 1);
}

int	echo(t_cmd *cmd, t_shell *shell)
{
	bool	flag;

	(void) shell;
	flag = is_echo_flag(cmd);
	if (flag && cmd->arg_count <= 1)
		return (SUCCESS);
	if (cmd->arg_count == 0)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (SUCCESS);
	}
	if (cmd->arg_count > 0)
		print_echo(cmd, flag);
	exit(0);
}
