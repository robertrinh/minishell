/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 19:16:50 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/05/26 13:32:46 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	shell_execute(t_shell *shell)
{
	t_cmd	*cmd;

	should_print("\n\n========execute========\n", shell->print_output);
	if (shell->cmd_table->cmd_count == 1)
	{
		cmd = shell->cmd_table->cmds[0];
		if (is_builtin(shell->builtin_main, cmd, B_NUM_MAIN))
			exec_builtin(shell->builtin_main, cmd, shell, B_NUM_MAIN);
		else
			g_exit_code = single_command(shell);
	}
	else
		g_exit_code = execute_commands(shell);
	return (g_exit_code);
}
