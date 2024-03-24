/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 19:16:50 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/03/22 18:27:13 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// * change later with jump table
// TODO add cd builtin
static bool catch_single_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!ft_strncmp(cmd->value, "exit", 5))
		g_exit_code = exit_shell(cmd, shell);
	else if (!ft_strncmp(cmd->value, "export", 7))
		g_exit_code = export(cmd, shell);
	else if (!ft_strncmp(cmd->value, "unset", 6))
		g_exit_code = unset(cmd, shell);
	return (SUCCESS);
} 

int		execute(t_shell *shell)
{
	should_print("\n\n========execute========\n", shell->print_output);

	if (shell->cmd_table->cmd_count == 1)
	{
		catch_single_builtin(shell->cmd_table->cmds[0], shell);
		g_exit_code = single_command(shell);
	}
	else
		g_exit_code = execute_commands(shell);
	
	return (0);
}
