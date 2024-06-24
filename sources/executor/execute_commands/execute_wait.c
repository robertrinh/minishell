/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_wait.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/22 21:17:34 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/23 18:19:08 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	Returns the signal of the last command, when execution is complete.

	WIFSIGNALED:	check if child process terminated through a signal.
	WIFEXITED:		check if child process terminated normally.
*/
int	wait_for_last_cmd(int child_count, int last_pid, t_shell *shell)
{
	int	i;
	int	status;
	int	last_status;
	int	waitpid_ret;

	i = 0;
	while (i < child_count)
	{
		waitpid_ret = waitpid(-1, &status, 0);
		if (waitpid_ret == last_pid)
			last_status = status;
		if (WIFEXITED(status) || WIFSIGNALED(status))
			i++;
	}
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else if (WIFSIGNALED(last_status))
	{
		shell->exit_code = WTERMSIG(last_status) + 128;
		return (shell->exit_code);
	}
	return (-1);
}
