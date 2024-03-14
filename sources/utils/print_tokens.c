/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_tokens.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/22 15:12:33 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/03/14 17:34:01 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_tokens(t_token *tokens)
{
	printf("\n\n========lexer========\n");
	while (tokens)
	{
		printf("%s - \t %s \n", type_to_string(tokens->type), tokens->value);
		tokens = tokens->next;
	}
}

void	print_strings(char **strings)
{
	int		i;

	i = 0;
	while (strings[i])
	{
		printf("%s\n", strings[i]);
		i++;
	}
}
