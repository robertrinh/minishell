/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 19:16:50 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/03/28 17:12:04 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		execute(t_shell *shell)
{
	should_print("\n\n========execute========\n", shell->print_output);

	if (shell->cmd_table->cmd_count == 1)
	{
		if (is_single_builtin(shell->cmd_table->cmds[0]->value))
			exec_single_builtin(shell->cmd_table->cmds[0], shell);
		g_exit_code = single_command(shell);
	}
	else
		g_exit_code = execute_commands(shell);
	// printf("global exit code after executing is %d\n", g_exit_code);
	return (g_exit_code);
}
