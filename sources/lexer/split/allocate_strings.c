/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   allocate_strings.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/07 13:01:10 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/01/17 17:17:28 by qtrinh        ########   odam.nl         */
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
		sp->strings[sp->i_str] = ft_calloc(sizeof(char), (ft_strlen(sp->buffer) + 1));
		ft_strlcpy(sp->strings[sp->i_str], sp->buffer, (ft_strlen(sp->buffer) + 1));
		sp->i_str++;
	}
	clear_buffer(sp);
	return (sp->strings);
}

char	**allocate_strings(t_split *sp)
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
