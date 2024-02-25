/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 19:16:50 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/02/25 19:06:22 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		execute(t_shell *shell)
{
	int	exit_code;	

	exit_code = 0;
	
	should_print("\n\n========execute========\n", shell->print_output);

	
	if (shell->cmd_table->cmd_count == 1)
		exit_code = single_command(shell);
	else
		exit_code = execute_commands(shell);
	
	return (0);
}
