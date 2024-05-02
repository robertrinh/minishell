/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   allocate_strings.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/07 13:01:10 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/05/02 15:48:32 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	clear_buffer(t_split *sp)
{
	int	i;

	i = 0;
	while (i <= sp->len)
	{
		sp->buffer[i] = 0;
		i++;
	}
}

static char	**allocate_substrings(t_split *sp)
{
	if (sp->i_buff > 0)
	{
		sp->strings[sp->i_str] = safe_strdup(sp->buffer);
		sp->i_str++;
	}
	clear_buffer(sp);
	return (sp->strings);
}

char	**allocate_strings_split(t_split *sp)
{
	sp->i = 0;
	while (sp->i < sp->len)
	{
		sp->i = skip_whitespace(sp);
		sp->i_buff = 0;
		while (sp->i < sp->len)
		{
			if (is_quote(sp->input[sp->i]) != 0)
			{
				buffer_quote(sp, is_quote(sp->input[sp->i]));
				break ;
			}
			if (is_white_space(sp->input[sp->i]))
				break ;
			if (check_operator(sp->input[sp->i], sp->input[sp->i + 1]) == 2)
			{
				if (sp->i_buff)
					break ;
				sp->buffer[sp->i_buff] = sp->input[sp->i];
				sp->buffer[sp->i_buff + 1] = sp->input[sp->i + 1];
				sp->i += check_operator(sp->input[sp->i], sp->input[sp->i + 1]);
				sp->i_buff += 2;
				break ;
			}
			else if (check_operator(sp->input[sp->i], sp->input[sp->i + 1]) == 1)
			{
				if (sp->i_buff)
					break ;
				sp->buffer[sp->i_buff] = sp->input[sp->i];
				sp->i += check_operator(sp->input[sp->i], sp->input[sp->i + 1]);
				sp->i_buff++;
				break ;
			}
			sp->buffer[sp->i_buff] = sp->input[sp->i];
			sp->i++;
			sp->i_buff++;
		}
		sp->buffer[sp->i_buff] = 0;
		sp->strings = allocate_substrings(sp);
	}
	sp->strings[sp->i_str] = 0;
	return (sp->strings);
}
