/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_quotes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/06 15:05:26 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/01/10 20:43:07 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool is_quote(char c)
{
	if (c == 34 || c ==39)
		return (true);
	return (false);
}

static bool contains_quote(char *s)
{
	if (ft_strchr(s, 34) || ft_strchr(s, 39))
		return (true);
	return (false);
}

t_token	*locate_quote_token(t_token *tokens, t_pos position)
{
	t_token	*tokens_current;

	if (position == BEFORE)
		tokens_current = tokens;
	else
		tokens_current = lst_rev(lst_copy(tokens));
	while (tokens_current)
	{
		if (contains_quote(tokens_current->value))
			return (tokens_current);
		tokens_current = tokens_current->next;
	}
	return (NULL);
}

static int	locate_quote_strr(int len, char *s)
{
	while (len >= 0)
	{
		if (is_quote(s[len]))
			break ;
		len--;
	}
	return (len);
}

static char *collect_quote(char *s, int len, int i_q, t_pos position)
{
	int		i;
	char	*buffer;

	i = 0;
	buffer = ft_calloc(sizeof(char), len + 1);
	if (buffer == NULL)
	{
		// clean_exit()
	}
	if (position == AFTER)
		i_q++;
	while (i <= len)
	{
		if (position == BEFORE)
		{
			buffer[i] = s[i];
			if (i == i_q)
				break ;
		}
		else
		{
			buffer[i] = s[i_q];
			i_q++;
		}
		i++;
	}
	return (buffer);
}

static char *buffer_quote(t_token *token, t_pos position)
{
	int 	i_quote;
	int		len;
	char	*buffer;

	len = ft_strlen(token->value);
	i_quote = locate_quote_strr(len, token->value);
	buffer = collect_quote(token->value, len, i_quote, position);
	return (buffer);
}

static char *buffer_quotes(t_token *first, t_token *last, t_pos position)
{
	char	*buffer;
	int		combined_len;

	buffer = ft_calloc(sizeof(char *), 1000);
	while (first)
	{
		combined_len = (ft_strlen(buffer) + ft_strlen(first->value) + 1);
		ft_strlcat(buffer, first->value, combined_len);
		if (first->i == (last->i - 1))
		{
			if (position == BEFORE)
				buffer = ft_strjoin(buffer, buffer_quote(last, BEFORE));
			else
				buffer = buffer_quote(last, AFTER);
			break ;
		}
		first = first->next;
	}
	return (buffer);
}

void	tokenize_quotes(t_shell *shell)
{
	t_token	*first_quote;
	t_token	*last_quote;
	char	*buff_before;
	char	*buff_after;

	first_quote = locate_quote_token(shell->tokens, BEFORE);
	last_quote = locate_quote_token(shell->tokens, AFTER);
	if (first_quote == NULL && last_quote == NULL)
	{
		// No quotes, continue
		return ;
	}

	// 1. Buffer values between outer quotes
	buff_before = buffer_quotes(first_quote, last_quote, BEFORE);
	buff_after = buffer_quotes(first_quote, last_quote, AFTER);
	printf("Buff BEFORE last quote: \t %s\n", buff_before);
	printf("Buff AFTER last quote:  \t %s\n", buff_after);
	if (buff_before)
	{
		// 1.1 Remove quote characters

		// 2. Romove middle tokens

		// 3. Incert new token
	}
}

// test "this long"and"complicated"quote
