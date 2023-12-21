/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:27:42 by qbeukelm          #+#    #+#             */
/*   Updated: 2023/12/21 18:12:21 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*lstlast(t_token *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static int	count_quotes(t_token *tokens_head)
{
	int quote_count;

	quote_count = 0;
	while (tokens_head)
	{
		// if (tokens_head->value == 34 || tokens_head->value == 39)
		// 	quote_count++;
		tokens_head = tokens_head->next;
	}
	// printf("quotes_count: %d\n", quote_count);
	return (quote_count);
}

static bool is_quotes_unmatched(t_token *tokens_head)
{
	count_quotes(tokens_head);
	return true;
}

static t_token	*build_split_tokens(char *buffer, char quote)
{
	// if buffer nil -> only one token
	t_token	*split_tokens_head;

	if (buffer)
	{
		split_tokens_head = token_constructor(buffer);
		split_tokens_head->next = token_constructor(&quote);
	}
	else
		split_tokens_head = token_constructor(buffer);
	return (split_tokens_head);
}


t_token	*split_quote_token(char *token_value)
{
	int 		i;
	int 		i_buff;
	char 		*buffer = NULL;
	t_token		*split_tokens;
	
	i = 0;
	i_buff = 0;
	while (token_value[i])
	{
		printf("split_quote_token i: %d", i);
		if (token_value[i] == 34 || token_value[i] == 39)
		{
			// Buffer make token
			// Quote make token
			split_tokens = build_split_tokens(buffer, token_value[i]);
			print_token(split_tokens);
			i_buff = 0;
		} 
		else
		{
			buffer[i_buff] = token_value[i];
			i_buff++;
		}
		i++;
	}
	return (split_tokens);
}

t_token *unpack_quotes(t_token *tokens_head)
{
	t_token *tokens_current;
	t_token	*split_tokens;

	tokens_current = tokens_head;
	while(tokens_current)
	{
		if (tokens_current->next->next)
		{
			printf("(Quote found: %p)\n", ft_strchr(tokens_current->next->value, 34));
			if (ft_strchr(tokens_current->next->value, 34))
			{
				split_tokens = split_quote_token(tokens_current->value);
				// Incert split tokens
				tokens_current->next = split_tokens;
				// split tokens last->next is next->next
				split_tokens = lstlast(split_tokens);
				split_tokens->next = tokens_current->next->next;
				// Free quotes token
				free(tokens_current->next);
			}
		}
		else
		{
			// TODO handle last two token
		}
		printf("before next\n");
		tokens_current = tokens_current->next;
		printf("next\n");
	}
	return (tokens_head);
}

t_token *quote_manager(t_token *tokens_head)
{
	printf("\n\n========quote manager========\n");
	if (is_quotes_unmatched(tokens_head))
	{
		// TODO exit
	}
	tokens_head = unpack_quotes(tokens_head);

	return (tokens_head);
}

