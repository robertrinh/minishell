/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_exit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/07 12:29:05 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/02/19 17:20:00 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int count_pipes(t_shell *shell)
{
	t_token		*current;
	int			count;
	
	current = shell->tokens;
	count = 0;
	while (current)
	{
		if (current->type == PIPE)
			count++;
		current = current->next;
	}
	return (count);
}

int	exit_with_message(t_error_messages error_code, t_message_colors color)
{
	printf("\n%s%s%s\n", color_codes[color], error_messages[error_code], RESET_COLOR);
	// TODO clean_exit()
	return (FAILURE);
}

void	finish_lexer(t_shell *shell)
{
	shell->single_quote = 0;
	shell->double_quote = 0;
}
