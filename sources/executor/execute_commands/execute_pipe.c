/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_pipe.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/22 21:17:02 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/04/24 19:33:46 by qtrinh        ########   odam.nl         */
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
		show_error_message(E_FORK, C_RED, "", X_FORK);
	handle_signals(CHILD);
	if (fork_id == 0)
	{
		if (dup2(pipe_out[WRITE], STDOUT_FILENO) < 0)
			show_error_message(E_DUP, C_RED, cmd->value, X_DUP);
		close(pipe_out[WRITE]);
		close(pipe_out[READ]);

		// TODO execute
		manage_execution(shell, cmd);
	}
	close(pipe_out[WRITE]);
}

void	mid_cmd(t_shell *shell, t_cmd *cmd, int pipe_in, int pipe_out[2])
{
	int	fork_id;

	signal(SIGINT, SIG_IGN);
	fork_id = fork();
	if (fork_id < 0)
		show_error_message(E_FORK, C_RED, "", X_FORK);
	handle_signals(CHILD);
	if (fork_id == 0)
	{
		if (dup2(pipe_out[WRITE], STDOUT_FILENO) < 0 || \
			dup2(pipe_in, STDIN_FILENO) < 0)
			show_error_message(E_DUP, C_RED, cmd->value, X_DUP);
		close(pipe_in);
		close(pipe_out[WRITE]);
		close(pipe_out[READ]);

		// TODO execute
		manage_execution(shell, cmd);
	}
	close(pipe_in);
	close(pipe_out[WRITE]);
}

int	final_cmd(t_shell *shell, t_cmd *cmd, int pipe_in)
{
	int	fork_id;

	signal(SIGINT, SIG_IGN);
	fork_id = fork();
	if (fork_id < 0)
		show_error_message(E_FORK, C_RED, "", X_FORK);
	handle_signals(CHILD);
	if (fork_id == 0)
	{
		if (dup2(pipe_in, STDIN_FILENO) < 0)
			show_error_message(E_DUP, C_RED, cmd->value, X_DUP);
		close(pipe_in);

		// TODO execute
		manage_execution(shell, cmd);
	}
	close(pipe_in);
	return (fork_id);
}