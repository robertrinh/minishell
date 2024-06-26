/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 14:45:13 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/06/26 13:47:58 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_echo_flag(char *arg, bool *flag)
{
	size_t	i;

	i = 0;
	if (arg[i] != '-')
		return (false);
	else
		i++;
	while (arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
	{
		*flag = true;
		return (true);
	}
	return (false);
}

static void	print_echo(t_cmd *cmd, int i, bool flag)
{
	while (i < cmd->arg_count)
	{
		write(STDOUT_FILENO, cmd->args[i], ft_strlen(cmd->args[i]));
		if (cmd->args[i + 1])
			write(STDOUT_FILENO, " ", 2);
		i++;
	}
	if (flag == false)
		write(1, "\n", 1);
}

int	echo(t_cmd *cmd, t_shell *shell)
{
	int		i;
	bool	flag;

	(void) shell;
	i = 0;
	flag = false;
	if (cmd->arg_count == 0)
	{
		write(STDOUT_FILENO, "\n", 2);
		exit(EXIT_SUCCESS);
	}
	if (cmd->arg_count <= 1 && is_echo_flag(cmd->args[i], &flag))
		exit(EXIT_SUCCESS);
	while (cmd->args[i] && is_echo_flag(cmd->args[i], &flag))
		i++;
	print_echo(cmd, i, flag);
	exit(EXIT_SUCCESS);
}
