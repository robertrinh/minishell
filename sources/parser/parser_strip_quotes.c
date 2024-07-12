/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_strip_quotes.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/24 09:51:56 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/07/12 14:25:03 by qtrinh        ########   odam.nl         */
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

// char	*new_strip_quotes(char *arg)
// {
// 	int		i;
// 	int		len;
// 	int		quote_type;
// 	char	*new_arg;

// 	i = 0;
// 	len = ft_strlen(arg);
// 	while (i < len)
// 	{
// 		if (is_quote(arg[i]))
// 		{
// 			quote_type = is_quote(arg[i]);
// 			new_arg = ft_str_remove_char(arg, i, quote_type);
// 			if (new_arg == NULL)
// 				return (NULL);
// 			arg = new_arg;
// 			i--;
// 			i = next_quote_char(arg, i, quote_type);
// 			if (is_quote(arg[i]) == quote_type)
// 			{
// 				new_arg = ft_str_remove_char(arg, i, quote_type);
// 				if (new_arg == NULL)
// 					return (NULL);
// 				free(arg);
// 				arg = new_arg;
// 			}
// 			i--;
// 			len = ft_strlen(arg);
// 		}
// 		i++;
// 	}
// 	return (arg);
// }

bool new_strip_quotes(char *arg, t_vec *vec)
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
				return (FAILURE);
			arg = new_arg;
			i--;
			i = next_quote_char(arg, i, quote_type);
			if (is_quote(arg[i]) == quote_type)
			{
				new_arg = ft_str_remove_char(arg, i, quote_type);
				if (new_arg == NULL)
					return (FAILURE);
				// free(arg);
				arg = new_arg;
			}
			i--;
			len = ft_strlen(arg);
		}
		i++;
	}
	ft_vec_push_str(vec, new_arg);
	return (SUCCESS);
}
