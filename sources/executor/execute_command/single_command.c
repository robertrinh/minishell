/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:28:14 by qbeukelm          #+#    #+#             */
/*   Updated: 2024/06/07 16:02:40 by qbeukelm         ###   ########.fr       */
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

void	should_exit_no_command(t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd_path, CMD_NOT_FOUND_STR, 1) == 0)
	{
		show_error_message(E_CMD_NOT_FOUND, C_RED, cmd->value, X_CMD);
		g_exit_code = 0;
		exit(g_exit_code);
	}
	else if (cmd->cmd_path == NULL)
	{
		g_exit_code = 0;
		exit(g_exit_code);
	}
}

t_validation	child_process(t_shell *shell)
{
	if (assign_out_redirects(shell->cmd_table->cmds[0]) == SUCCESS)
	{
		if (is_builtin(shell->builtin_child, shell->cmd_table->cmds[0], B_NUM_CHILD))
			exec_builtin(shell->builtin_child, shell->cmd_table->cmds[0], shell, B_NUM_CHILD);
		else
		{
			prepare_command(shell, 0);
			should_exit_no_command(shell->cmd_table->cmds[0]);
			return (execute_command(shell, 0));
		}
	}
	return (FAILURE);
}

int	single_command(t_shell *shell)
{
	pid_t			pid;
	int				stat_loc;

	stat_loc = 0;
	if (redirect_in_files(shell->cmd_table->cmds[0], &stat_loc) == SUCCESS)
		g_exit_code = 0;
	if (stat_loc >= 1)
		stat_loc = 1;
	if (WIFSIGNALED(stat_loc))
		return (g_exit_code = X_SIG_HEREDOC);
	handle_signals(CHILD);
	pid = fork();
	if (pid < 0)
		exit_with_message(E_FORK, C_RED, X_FAILURE);
	if (pid == 0)
		child_process(shell);
	else if (pid > 0)
	{
		waitpid(pid, &stat_loc, 0);
		if (WIFEXITED(stat_loc))
			return (WEXITSTATUS(stat_loc));
	}
	return (g_exit_code);
}
