/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_strip_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 09:51:56 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/07/12 16:14:03 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft/lib_vector/vector.h"

static int	next_quote_char(char *arg, int i, int quote_char)
{
	int	len;

	i++;
	len = ft_strlen(arg);
	while (i < len)
	{
		if (arg[i] == quote_char)
			return (i);
		i++;
	}
	return (i);
}

char	*new_strip_quotes(char *arg)
{
	int		i;
	int		len;
	int		quote_type;
	char	*new_arg;

	i = 0;
	len = ft_strlen(arg);
	while (i < len)
	{
		if (is_quote(arg[i]))
		{
			quote_type = is_quote(arg[i]);
			new_arg = ft_str_remove_char(arg, i, quote_type);
			if (new_arg == NULL)
				return (NULL);
			i--;
			i = next_quote_char(arg, i, quote_type);
			if (is_quote(arg[i]) == quote_type)
			{
				new_arg = ft_str_remove_char(new_arg, i, quote_type);
				if (new_arg == NULL)
					return (NULL);
			}
			i--;
			len = ft_strlen(arg);
		}
		i++;
	}
	free(arg);
	return (new_arg);
}
