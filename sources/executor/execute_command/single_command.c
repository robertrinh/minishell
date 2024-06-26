/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_command.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 14:28:14 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/06/26 13:52:54 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_validation	assign_out_redirects(t_cmd *cmd, t_shell *shell)
{
	t_validation	validation;

	validation = SUCCESS;
	if (cmd->fd_out)
		validation = redirect_out(cmd, shell);
	return (validation);
}

static void	should_exit_no_command(t_cmd *cmd, t_shell *shell)
{
	if (cmd->cmd_path == NULL)
	{
		shell->exit_code = 0;
		exit(shell->exit_code);
	}
	else if (ft_strncmp(cmd->cmd_path, CMD_NOT_FOUND_STR, 1) == 0)
	{
		show_error_message(E_CMD_NOT_FOUND, shell, cmd->value, X_CMD);
		exit(shell->exit_code);
	}
}

t_validation	child_process(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmd_table->cmds[0];
	if (assign_out_redirects(cmd, shell) == SUCCESS)
	{
		if (is_builtin(shell->builtin_child, cmd, B_NUM_CHILD))
			exec_builtin(shell->builtin_child, cmd, shell, B_NUM_CHILD);
		else
		{
			prepare_command(shell, 0);
			should_exit_no_command(cmd, shell);
			return (execute_command(shell, 0));
		}
	}
	return (FAILURE);
}

int	single_command(t_shell *shell)
{
	pid_t			pid;
	int				st_loc;

	st_loc = 0;
	if (redirect_in_files(shell->cmd_table->cmds[0], &st_loc, shell) == SUCCESS)
		shell->exit_code = 0;
	if (st_loc >= 1)
		st_loc = 1;
	if (WIFSIGNALED(st_loc))
		return (shell->exit_code = X_SIG_HEREDOC);
	handle_signals(CHILD);
	pid = fork();
	if (pid < 0)
		exit_with_message(E_FORK, shell, X_FAILURE);
	if (pid == 0)
		child_process(shell);
	else if (pid > 0)
	{
		waitpid(pid, &st_loc, 0);
		if (g_signal == SIGQUIT)
			shell->exit_code = X_SIG_BACKSLASH;
		if (WIFEXITED(st_loc))
			return (WEXITSTATUS(st_loc));
	}
	return (shell->exit_code);
}
