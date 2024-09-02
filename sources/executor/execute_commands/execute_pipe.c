/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:17:02 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/09/02 13:28:07 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	manage_execution(t_shell *shell, t_cmd *cmd)
{
	if (cmd->fd_out)
		redirect_out(cmd, shell);
	if (is_main_builtin(cmd->value))
		exec_builtin(shell, cmd);
	else
		execute_piped_command(shell, cmd);
}

void	first_cmd(t_shell *shell, t_cmd *cmd, int pipe_out[2])
{
	int	fork_id;

	signal(SIGINT, SIG_IGN);
	fork_id = fork();
	if (fork_id < 0)
		exit_with_message(E_FORK, shell, X_FAILURE);
	handle_signals(CHILD);
	if (fork_id == 0)
	{
		if (dup2(pipe_out[WRITE], STDOUT_FILENO) < 0)
		{
			show_error(E_DUP, shell, cmd->value, X_FAILURE);
			if (close_fds(pipe_out[WRITE], pipe_out[READ], -1) == false)
				exit_with_message(E_CLOSE, shell, X_FAILURE);
			exit(shell->exit_code);
		}
		if (close_fds(pipe_out[WRITE], pipe_out[READ], -1) == false)
			exit_with_message(E_CLOSE, shell, X_FAILURE);
		manage_execution(shell, cmd);
	}
	if (close_fds(pipe_out[WRITE], -1, -1) == false)
		show_error(E_CLOSE, shell, "parent first cmd", X_FAILURE);
}

void	mid_cmd(t_shell *shell, t_cmd *cmd, int pipe_in, int pipe_out[2])
{
	int	fork_id;

	signal(SIGINT, SIG_IGN);
	fork_id = fork();
	if (fork_id < 0)
		exit_with_message(E_FORK, shell, X_FAILURE);
	handle_signals(CHILD);
	if (fork_id == 0)
	{
		if (dup2(pipe_out[WRITE], STDOUT_FILENO) < 0 || \
			dup2(pipe_in, STDIN_FILENO) < 0)
		{
			show_error(E_DUP, shell, cmd->value, X_FAILURE);
			if (close_fds(pipe_out[WRITE], pipe_in, -1) == false)
				exit_with_message(E_CLOSE, shell, X_FAILURE);
			exit(shell->exit_code);
		}
		if (close_fds(pipe_in, pipe_out[WRITE], pipe_out[READ]) == false)
			exit_with_message(E_CLOSE, shell, X_FAILURE);
		manage_execution(shell, cmd);
	}
	if (close_fds(pipe_in, pipe_out[WRITE], -1) == false)
		show_error(E_CLOSE, shell, "parent mid cmd", X_FAILURE);
}

int	final_cmd(t_shell *shell, t_cmd *cmd, int pipe_in)
{
	int	fork_id;

	signal(SIGINT, SIG_IGN);
	fork_id = fork();
	if (fork_id < 0)
		exit_with_message(E_FORK, shell, X_FAILURE);
	handle_signals(CHILD);
	if (fork_id == 0)
	{
		if (dup2(pipe_in, STDIN_FILENO) < 0)
		{
			show_error(E_DUP, shell, cmd->value, X_FAILURE);
			if (close_fds(pipe_in, -1, -1) == false)
				exit_with_message(E_CLOSE, shell, X_FAILURE);
			exit(shell->exit_code);
		}
		if (close_fds(pipe_in, -1, -1) == false)
			exit_with_message(E_CLOSE, shell, X_FAILURE);
		manage_execution(shell, cmd);
	}
	if (close_fds(pipe_in, -1, -1) == false)
		show_error(E_CLOSE, shell, "parent last cmd", X_FAILURE);
	return (fork_id);
}
