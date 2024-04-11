/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_command.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 14:28:14 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/04/11 14:57:31 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_validation	assign_out_redirects(t_cmd *cmd)
{
	t_validation	validation;

	validation = SUCCESS;
	if (cmd->fd_out)
		validation = redirect_out(cmd);
	return (validation);
}

void	child_process(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmd_table->cmds[0];
	if (assign_out_redirects(shell->cmd_table->cmds[0]) == SUCCESS)
	{
		if (is_builtin(shell->builtin_child, cmd, B_NUM_CHILD))
			exec_builtin(shell->builtin_child, cmd, shell, B_NUM_CHILD);
		else
		{
			prepare_command(shell, 0);
			execute_command(shell, 0);
		}
	}
	return ;
}

int	single_command(t_shell *shell)
{
	pid_t			pid;
	int				status;

	status = 0;
	handle_signals(CHILD);
	redirect_in_files(shell->cmd_table->cmds[0]);
	pid = fork();
	if (pid == -1)
	{
		// TODO exit / return with error message fork
	}
	if (pid == 0)
		child_process(shell);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (g_exit_code);
}
