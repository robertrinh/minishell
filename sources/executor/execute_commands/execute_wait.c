/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_wait.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/22 21:17:34 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/04/24 19:19:49 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	Returns the signal of the last command, when exicution complete.

	WIFSIGNALED:	check if child process terminated because it received a signal.
	WIFEXITED:		check if child process terminated normally.
*/
int	wait_for_last_cmd(int child_count, int last_pid)
{
	int	i;
	int	status;
	int	last_status;
	int	waitpid_ret;

	i = 0;
	while (i < child_count)
	{
		waitpid_ret = waitpid(-1, &status, 0);
		if (waitpid_ret < 0)
			show_error_message(E_WAITPID, C_RED, "", X_WAITPID);
		if (waitpid_ret == last_pid)
			last_status = status;
		if (WIFEXITED(status))
			i++;
	}
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	return (-1);
}
