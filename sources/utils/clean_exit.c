/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_exit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/07 12:29:05 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/04/07 12:16:44 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	lexer_finish(t_shell *shell)
{
	shell->single_quote = 0;
	shell->double_quote = 0;
}

void	shell_finish(t_shell *shell)
{
	lexer_finish(shell);
	dup2(shell->original_stdin, STDIN_FILENO);
	should_print("\n--------------------End--------------------\n\n", shell->print_output);
}
