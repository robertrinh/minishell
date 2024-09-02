/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:16:50 by qbeukelm          #+#    #+#             */
/*   Updated: 2024/09/02 13:27:46 by qbeukelm         ###   ########.fr       */
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
		if (is_main_builtin(cmd->value))
			shell->exit_code = \
				exec_builtin(shell, cmd);
		else
			shell->exit_code = single_command(shell);
	}
	else
		shell->exit_code = execute_commands(shell);
	return (shell->exit_code);
}
