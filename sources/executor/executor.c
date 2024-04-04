/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 19:16:50 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/04/04 17:43:37 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		execute(t_shell *shell)
{
	should_print("\n\n========execute========\n", shell->print_output);

	if (shell->cmd_table->cmd_count == 1)
	{
		if (is_special_builtin(shell->cmd_table->cmds[0]->value))
		{
			printf("is builtin\n");
			exec_special_builtin(shell->cmd_table->cmds[0], shell);
		}
		else
			g_exit_code = single_command(shell);
	}
	else
		g_exit_code = execute_commands(shell);
	return (g_exit_code);
}
