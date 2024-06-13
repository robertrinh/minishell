/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_pipe.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/22 21:17:02 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/13 15:42:20 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	manage_execution(t_shell *shell, t_cmd *cmd)
{
	if (cmd->fd_out)
		redirect_out(cmd);
	if (is_builtin(shell->builtin_main, cmd, B_NUM_MAIN))
		exec_builtin(shell->builtin_main, cmd, shell, B_NUM_MAIN);
	else
		execute_piped_command(shell, cmd);
}

void	first_cmd(t_shell *shell, t_cmd *cmd, int pipe_out[2])
{
	int	fork_id;

	signal(SIGINT, SIG_IGN);
	fork_id = fork();
	if (fork_id < 0)
		exit_with_message(E_FORK, C_RED, X_FAILURE);
	handle_signals(CHILD);
	if (fork_id == 0)
	{
		if (dup2(pipe_out[WRITE], STDOUT_FILENO) < 0)
		{
			show_error_message(E_DUP, C_RED, cmd->value, X_FAILURE);
			if (close_fds(pipe_out[WRITE], pipe_out[READ], -1) == false)
				exit_with_message(E_CLOSE, C_RED, X_FAILURE);
			exit(g_exit_code);
		}
		if (close_fds(pipe_out[WRITE], pipe_out[READ], -1) == false)
			exit_with_message(E_CLOSE, C_RED, X_FAILURE);
		manage_execution(shell, cmd);
	}
	if (close_fds(pipe_out[WRITE], -1, -1) == false)
		show_error_message(E_CLOSE, C_RED, "parent first cmd", X_FAILURE);
}

void	mid_cmd(t_shell *shell, t_cmd *cmd, int pipe_in, int pipe_out[2])
{
	int	fork_id;

	signal(SIGINT, SIG_IGN);
	fork_id = fork();
	if (fork_id < 0)
		exit_with_message(E_FORK, C_RED, X_FAILURE);
	handle_signals(CHILD);
	if (fork_id == 0)
	{
		if (dup2(pipe_out[WRITE], STDOUT_FILENO) < 0 || \
			dup2(pipe_in, STDIN_FILENO) < 0)
		{
			show_error_message(E_DUP, C_RED, cmd->value, X_FAILURE);
			if (close_fds(pipe_out[WRITE], pipe_in, -1) == false)
				exit_with_message(E_CLOSE, C_RED, X_FAILURE);
			exit(g_exit_code);
		}
		if (close_fds(pipe_in, pipe_out[WRITE], pipe_out[READ]) == false)
			exit_with_message(E_CLOSE, C_RED, X_FAILURE);
		manage_execution(shell, cmd);
	}
	if (close_fds(pipe_in, pipe_out[WRITE], -1) == false)
		show_error_message(E_CLOSE, C_RED, "parent mid cmd", X_FAILURE);
}

int	final_cmd(t_shell *shell, t_cmd *cmd, int pipe_in)
{
	int	fork_id;

	signal(SIGINT, SIG_IGN);
	fork_id = fork();
	if (fork_id < 0)
		exit_with_message(E_FORK, C_RED, X_FAILURE);
	handle_signals(CHILD);
	if (fork_id == 0)
	{
		if (dup2(pipe_in, STDIN_FILENO) < 0)
		{
			show_error_message(E_DUP, C_RED, cmd->value, X_FAILURE);
			if (close_fds(pipe_in, -1, -1) == false)
				exit_with_message(E_CLOSE, C_RED, X_FAILURE);
			exit(g_exit_code);
		}
		if (close_fds(pipe_in, -1, -1) == false)
			exit_with_message(E_CLOSE, C_RED, X_FAILURE);
		manage_execution(shell, cmd);
	}
	if (close_fds(pipe_in, -1, -1) == false)
		show_error_message(E_CLOSE, C_RED, "parent last cmd", X_FAILURE);
	return (fork_id);
}
