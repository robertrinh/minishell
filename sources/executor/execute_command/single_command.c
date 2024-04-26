/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:28:14 by qbeukelm          #+#    #+#             */
/*   Updated: 2024/04/26 16:49:20 by qbeukelm         ###   ########.fr       */
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
	char	*cmd_value;

	cmd = shell->cmd_table->cmds[0];
	if (assign_out_redirects(shell->cmd_table->cmds[0]) == SUCCESS)
	{
		if (is_builtin(shell->builtin_child, cmd, B_NUM_CHILD))
			exec_builtin(shell->builtin_child, cmd, shell, B_NUM_CHILD);
		else
		{
			prepare_command(shell, 0);
			if (shell->cmd_table->cmds[0]->cmd_path == NULL)
			{
				cmd_value = shell->cmd_table->cmds[0]->value;
				show_error_message(E_CMD_NOT_FOUND, C_RED, cmd_value, X_CMD);
				exit(g_exit_code);
			}
			execute_command(shell, 0);
		}
	}
}

int	single_command(t_shell *shell)
{
	pid_t			pid;
	int				stat_loc;

	stat_loc = 0;
	redirect_in_files(shell->cmd_table->cmds[0], &stat_loc);
	if (stat_loc >= 1)
		stat_loc = 1;
	if (WIFSIGNALED(stat_loc))
		return (g_exit_code);
	handle_signals(CHILD);
	pid = fork();
	if (pid == -1)
	{
		// TODO exit / return with error message fork
	}
	if (pid == 0)
		child_process(shell);
	else if (pid > 0)
	{
		waitpid(pid, &stat_loc, 0);
		printf("stat_loc: %d\n", stat_loc);
		if (WIFEXITED(stat_loc))
			return (WEXITSTATUS(stat_loc));
	}
	return (g_exit_code);
}
