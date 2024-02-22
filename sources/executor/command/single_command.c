/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_command.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 14:28:14 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/02/22 17:15:11 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void print_2d_char(char **arr)
{
	int i = 0;
	while (arr[i])
	{
		printf("2D[%d] %s\n", i, arr[i]);
		i++;
	}
}

void	child_process(t_shell *shell)
{
	//TODO pipe dupe fd
	//TODO redirect dupe fd -> fd_in/fd_out
	//TODO run builtin instead of command
	execute_command(shell);
}

int	single_command(t_shell *shell)
{
	pid_t	pid;
	int	exit_code;

	//TODO expanders
	//TODO redirects
	//TODO run builtins one command
	pid = fork();
	if (pid == -1)
	{
		//TODO exit
	}
	if (pid == 0)
		child_process(shell);
	waitpid(pid, &exit_code, 0);
	return (WEXITSTATUS(exit_code));
}
