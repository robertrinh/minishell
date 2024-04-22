/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_commands.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/22 21:09:40 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/04/22 21:24:46 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_last_cmd(int cmd_count, int i)
{
	if (i == cmd_count - 1)
		return (true);
	return (false);
}

static int pipe_commands(t_shell *shell, t_cmd *cmd, t_childs *childs, bool is_last_cmd)
{
	int				last_pid;
	static int		flip = 0; 

	last_pid = 0;

	if (is_last_cmd == false)
	{
		// Create a new pipe
		if (pipe(childs->pipe_fd[flip]) < 0)
			show_error_message(E_PIPE_FAIL, C_RED, cmd->value, X_PIPE);
	}
	if (childs->child_count == 0)
	{
		// First command
		first_cmd(shell, cmd, childs->pipe_fd[flip]);
	}
	else if (is_last_cmd)
	{
		// Last command
		last_pid = final_cmd(shell, cmd, childs->pipe_fd[!flip][0]);
	}
	else
	{
		// Middle command
		mid_cmd(shell, cmd, childs->pipe_fd[!flip][0], childs->pipe_fd[flip]);
	}

	flip = !flip;
	return (last_pid);
}

static int execute_cmd_for(t_shell *shell, int i, t_childs *childs)
{
	int			last_cmd;
	t_cmd		*cmd;

	last_cmd = is_last_cmd(shell->cmd_table->cmd_count, i);
	cmd = shell->cmd_table->cmds[i];
	if (cmd->fd_in)
		redirect_in_files(cmd);
	prepare_command(shell, i);
	return (pipe_commands(shell, cmd, childs, last_cmd));
}

int	execute_commands(t_shell *shell)
{
	int			i;
	int			last_pid;
	t_cmd		*cmd;
	t_childs	childs;
	int			return_value;

	i = 0;
	last_pid = 0;
	childs.child_count = 0;
	while (i < shell->cmd_table->cmd_count)
	{
		last_pid = execute_cmd_for(shell, i, &childs);
		childs.child_count++;
		i++;
	}
	return_value = wait_for_last_cmd(childs.child_count, last_pid);
	return (return_value);
}
