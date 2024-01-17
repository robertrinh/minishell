/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_exit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/07 12:29:05 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/01/17 16:14:48 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exit_with_message(e_error_messages error_code, e_message_colors color)
{
	printf("\n%s%s%s\n", color_codes[color], error_messages[error_code], RESET_COLOR);
	// TODO clean_exit()
	return (FAILURE);
}

void	finish_command(t_shell *shell)
{
	shell->cmd->single_quote = 0;
	shell->cmd->double_quote = 0;
}
