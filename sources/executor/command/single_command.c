/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:28:14 by qbeukelm          #+#    #+#             */
/*   Updated: 2024/04/05 15:15:00 by qbeukelm         ###   ########.fr       */
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
	if (assign_out_redirects(shell->cmd_table->cmds[0]) == SUCCESS)
	{
		if (is_builtin(shell->cmd_table->cmds[0]->value))
			exec_builtin(shell->cmd_table->cmds[0], shell);
		else
		{
			prepare_command(shell, 0);
			execute_command(shell, 0);
		}
		return ;
	}
	return ;
}

int	single_command(t_shell *shell)
{
	pid_t			pid;
	int				exit_status;

	exit_status = 0;
	handle_signals(CHILD);
	redirect_in_files(shell->cmd_table->cmds[0]);
	pid = fork();
	if (pid == -1)
	{
		// TODO exit
	}
	if (pid == 0)
		child_process(shell);
	else if (pid > 0)
		waitpid(pid, &exit_status, 0);

	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return(WEXITSTATUS(g_exit_code));
}
