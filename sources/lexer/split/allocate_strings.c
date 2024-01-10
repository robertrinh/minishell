/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   allocate_strings.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/07 13:01:10 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/01/07 13:12:46 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char **allocate_substrings(t_split *sp)
{
	if (sp->i_buff > 0)
	{
		sp->strings[sp->i_str] = ft_calloc(sizeof(char), (ft_strlen(sp->buffer) + 1));
		ft_strlcpy(sp->strings[sp->i_str], sp->buffer, (ft_strlen(sp->buffer) + 1));
		sp->i_str++;
	}
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
			if (sp->input[sp->i] == 32)
			{
				sp->buffer[sp->i_buff] = 32;
				sp->i_buff++;
				break ;
			}
			if (check_operator(sp->input[sp->i], sp->input[sp->i + 1]) == 2)
			{
				if(sp->i_buff)
					break ;
				sp->buffer[sp->i_buff] = sp->input[sp->i];
				sp->buffer[sp->i_buff + 1] = sp->input[sp->i + 1];
				sp->i += check_operator(sp->input[sp->i], sp->input[sp->i + 1]);
				sp->i_buff += 2;
				break ;
			} 
			else if (check_operator(sp->input[sp->i], sp->input[sp->i + 1]) == 1)
			{
				if(sp->i_buff)
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
