/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_tokens.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/22 15:12:33 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/03/14 18:33:36 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*type_to_string(t_token_type type)
{
	switch (type)
	{
		case COMMAND:
			return ("command  ");
		case ARGUMENT:
			return ("argument ");
		case PIPE:
			return ("pipe     ");
		case REDIRECT:
			return ("redirect ");
		case REDIR_IN:
			return ("in       ");
		case REDIR_IN_APPEND:
			return ("in_append");
		case REDIR_OUT:
			return ("out      ");
		case END_OF_FILE:
			return ("eof      ");
		case S_QUOTE:
			return ("s_quote  ");
		case D_QUOTE:
			return ("d_quote  ");
		case ARGFILE:
			return ("argfile  ");
		default:
			return ("none     ");
	}
}

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
