/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:16:50 by qbeukelm          #+#    #+#             */
/*   Updated: 2024/03/21 15:05:53 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool catch_single_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!ft_strncmp(cmd->value, "exit", 5))
		exit_shell(cmd, shell);
	
	// else if (!ft_strncmp(cmd->value, "export", 7))
	// 	export(cmd, shell);
	return (SUCCESS);
} //*change later with jump table

int		execute(t_shell *shell)
{
	int	exit_code;	

	exit_code = 0;
	should_print("\n\n========execute========\n", shell->print_output);

	if (shell->cmd_table->cmd_count == 1)
	{
		catch_single_builtin(shell->cmd_table->cmds[0], shell);
		exit_code = single_command(shell);
	}
	else
		exit_code = execute_commands(shell);
	
	return (0);
}
