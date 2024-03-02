/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_command.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 14:28:14 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/03/02 11:26:16 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	assign_redirects(t_cmd *cmd)
{
	int 	*fd_ins;
	int		*fd_heredocs;

	if (cmd->heredoc)
		fd_heredocs = collect_heredocs(cmd);
	if (cmd->fd_in)
		fd_ins = collect_fd_in_files(cmd);
	if (cmd->fd_in || cmd->heredoc)
		redirect_in_files(cmd, fd_ins, fd_heredocs);
	if (cmd->fd_out)
		redirect_out(cmd);
	return (SUCCESS);
}

void	child_process(t_shell *shell)
{
	//TODO redirect dupe fd -> fd_in/fd_out
	//TODO run builtin instead of command
	open_in_redirects(shell->cmd_table->cmds[0]);
	assign_redirects(shell->cmd_table->cmds[0]);
	if (is_builtin(shell->cmd_table->cmds[0]->value))
	{
		exec_builtin(shell->cmd_table->cmds[0]);
		return ;
	}
	prepare_command(shell, 0);
	execute_command(shell, 0);
}

int	single_command(t_shell *shell)
{
	pid_t	pid;
	int	exit_code;

	//TODO expanders
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
