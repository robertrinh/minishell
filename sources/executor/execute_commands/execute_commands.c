/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_commands.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/22 21:09:40 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/21 17:29:18 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_last_cmd(int cmd_count, int i)
{
	if (i == cmd_count - 1)
		return (true);
	return (false);
}

static int	pipe_commands(t_shell *sh, t_cmd *cmd, t_childs *ch, bool last_cmd)
{
	int				last_pid;
	static int		flip = 0;

	last_pid = 0;
	if (last_cmd == false)
	{
		if (pipe(ch->pipe_fd[flip]) < 0)
			exit_with_message(E_PIPE_FAIL, sh, X_FAILURE);
	}
	if (ch->child_count == 0)
		first_cmd(sh, cmd, ch->pipe_fd[flip]);
	else if (last_cmd)
		last_pid = final_cmd(sh, cmd, ch->pipe_fd[!flip][0]);
	else
		mid_cmd(sh, cmd, ch->pipe_fd[!flip][0], ch->pipe_fd[flip]);
	flip = !flip;
	return (last_pid);
}

static int	execute_cmd_for(t_shell *shell, int i, t_childs *ch)
{
	int			last_cmd;
	t_cmd		*cmd;
	int			stat_loc;

	stat_loc = 0;
	last_cmd = is_last_cmd(shell->cmd_table->cmd_count, i);
	cmd = shell->cmd_table->cmds[i];
	if (cmd->fd_in)
		if (redirect_in_files(cmd, &stat_loc, shell) == SUCCESS)
			shell->exit_code = 0;
	if (stat_loc >= 1)
		stat_loc = 1;
	if (WIFSIGNALED(stat_loc))
	{
		shell->exit_code = X_SIG_HEREDOC;
		return (-1);
	}
	prepare_command(shell, i);
	return (pipe_commands(shell, cmd, ch, last_cmd));
}

int	execute_commands(t_shell *shell)
{
	int			i;
	int			last_pid;
	t_childs	ch;
	int			return_value;

	i = 0;
	last_pid = 0;
	ch.child_count = 0;
	while (i < shell->cmd_table->cmd_count)
	{
		last_pid = execute_cmd_for(shell, i, &ch);
		if (last_pid < 0)
			return (shell->exit_code);
		ch.child_count++;
		i++;
	}
	return_value = wait_for_last_cmd(ch.child_count, last_pid, shell);
	return (return_value);
}
