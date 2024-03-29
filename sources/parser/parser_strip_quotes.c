/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_strip_quotes.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/24 09:51:56 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/29 22:02:25 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *char_to_string(char c)
{
	char *str;

	str = safe_malloc(sizeof(char *) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

static char *strip_quotes_forward(char *arg, int quote_char)
{
	int		i;
	int		len;
	char	*quote_str;

	i = 0;
	len = ft_strlen(arg);
	while (i < len)
	{
		if (arg[i] == quote_char)
		{
			quote_str = char_to_string(quote_char);
			arg = ft_str_remove(arg,  quote_str);
			free(quote_str);
			i--;
		}
		i++;
	}
	return (arg);
}

char	*strip_quote_for_type(char *arg, int quote_char)
{
	arg = strip_quotes_forward(arg, quote_char);
	return (arg);
}
