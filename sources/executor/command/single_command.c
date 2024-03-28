/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_command.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 14:28:14 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/03/28 15:29:59 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_validation	assign_redirects(t_cmd *cmd)
{
	t_validation	validation;
	int 			*fd_ins;
	int				*fd_heredocs;

	validation = SUCCESS;
	// if (cmd->heredoc)
	// 	fd_heredocs = collect_heredocs(cmd);
	// if (cmd->fd_in)
	// 	fd_ins = collect_fd_in_files(cmd);
	// if (cmd->fd_in || cmd->heredoc)
	// 	redirect_in_files(cmd, fd_ins, fd_heredocs);
	if (cmd->fd_out)
		validation = redirect_out(cmd);
	return (validation);
}

t_validation	child_process(t_shell *shell)
{
	open_in_redirects(shell->cmd_table->cmds[0]);
	if (assign_redirects(shell->cmd_table->cmds[0]) == SUCCESS)
	{
		if (is_builtin(shell->cmd_table->cmds[0]->value))
			exec_builtin(shell->cmd_table->cmds[0], shell);
		else
		{
			prepare_command(shell, 0);
			execute_command(shell, 0);
		}
		return (SUCCESS);
	}
	return (FAILURE);
}

t_validation	single_command(t_shell *shell)
{
	t_validation	validation;
	pid_t			pid;
	int				exit_status;

	pid = fork();
	handle_signals(CHILD);
	if (pid == -1)
	{
		// TODO exit
	}
	if (pid == 0)
		validation = child_process(shell);
	else if (pid > 0)
		waitpid(pid, &exit_status, 0);
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return (validation); // *in case of abnormal child process termination
}
