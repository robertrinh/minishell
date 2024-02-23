/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_command.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 14:28:14 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/02/23 16:26:49 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	child_process(t_shell *shell)
{
	//TODO redirect dupe fd -> fd_in/fd_out
	//TODO run builtin instead of command
	prepare_command(shell, 0);
	open_redirects(shell->cmd_table->cmds[0]);
	print_cmds(shell->cmd_table);
	execute_command(shell, 0);
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
