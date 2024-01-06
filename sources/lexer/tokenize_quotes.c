/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:05:26 by qbeukelm          #+#    #+#             */
/*   Updated: 2024/01/06 17:03:30 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*locate_first_quote(t_token *tokens)
{
	t_token *tokens_current;

	tokens_current = tokens;
	while (tokens_current)
	{
		if (ft_strchr(tokens_current->value, 34) || ft_strchr(tokens_current->value, 39))
			return (tokens_current);
		tokens_current = tokens_current->next;
	}
	return (NULL);
}

t_token	*locate_last_quote(t_token *tokens)
{
	t_token	*tokens_current;

	tokens_current = lst_rev(lst_copy(tokens));
	while (tokens_current)
	{
		if (ft_strchr(tokens_current->value, 34) || ft_strchr(tokens_current->value, 39))
			return (tokens_current);
		tokens_current = tokens_current->next;
	}

	return (NULL);
}

static char *buffer_quotes(t_token *first, t_token *last)
{
	char *buffer;

	buffer = ft_calloc(sizeof(char *), 1000);
	while (first)
	{
		ft_strlcat(buffer, first->value, (ft_strlen(buffer) + ft_strlen(first->value) + 1));
		if (first->i == last->i)
			break ;
		first = first->next;
	}
	return (buffer);
}

void	tokenize_quotes(t_shell *shell)
{
	t_token	*first_quote;
	t_token	*last_quote;
	char	*buffer;

	first_quote = locate_first_quote(shell->tokens);
	last_quote = locate_last_quote(shell->tokens);
	buffer = NULL;
	if (first_quote == NULL && last_quote == NULL)
	{
		// No quotes, continue
		return ;
	}

	// 1. Buffer values between outer quotes
	buffer = buffer_quotes(first_quote, last_quote);
	printf("Quote buffer: %s\n", buffer);
	//TODO split token after last quote with no spacebar
	// 1.1 Remove quote characters

	// 2. Romove middle tokens

	// 3. Incert new token

	

}
