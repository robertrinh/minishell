/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:29:05 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/02/29 13:55:03 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exit_with_message(t_error_messages error_code, t_message_colors color, int exit_code)
{
	printf("\n%s%s%s\n\n", color_codes[color], error_messages[error_code], RESET_COLOR);
	exit(exit_code);
	return (FAILURE);
}

void	finish_lexer(t_shell *shell)
{
	shell->single_quote = 0;
	shell->double_quote = 0;
}
