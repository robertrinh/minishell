/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_exit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/07 12:29:05 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/01/07 12:33:03 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_token(t_token *tokens)
{
	printf("\n\n========print tokens========\n");
	while (tokens)
	{
		printf("%s \n", tokens->value);
		tokens = tokens->next;
	}
}

void	finish_command(t_shell *shell)
{
	shell->cmd->single_quote = 0;
	shell->cmd->double_quote = 0;
}
