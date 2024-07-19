/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_strip_quotes.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/24 09:51:56 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/07/19 17:57:24 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool new_strip_quotes(char *arg, t_vec *vec, t_shell *shell)
{
	int		i;
	int		len;
	int		quote_type;

	i = 0;
	len = ft_strlen(arg);
	while (i < len)
	{
		if (is_quote(arg[i]))
		{
			quote_type = is_quote(arg[i]);
			i++;
			while (arg[i] != quote_type)
			{
				if (!ft_vec_push(vec, arg[i]))
					return (show_error_message(E_MALLOC, shell, "", 1));
				i++;
			}
		}
		else
			if (!ft_vec_push(vec, arg[i]))
				return (show_error_message(E_MALLOC, shell, "", 1));
		i++;
	}
	return (SUCCESS);
}
