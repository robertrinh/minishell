/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   buffer_quote.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 21:58:11 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/05/27 22:06:11 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	add_char_to_buff(t_split *sp)
{
	sp->buffer[sp->i_buff] = sp->input[sp->i];
	sp->i_buff++;
	sp->i++;
}

int	is_quote(char c)
{
	if (c == D_QUOTE_CHAR)
		return (c);
	else if (c == S_QUOTE_CHAR)
		return (c);
	return (0);
}

void	buffer_quote(t_split *sp, int quote_type)
{
	add_char_to_buff(sp);
	while (sp->i < sp->len)
	{
		if (is_quote(sp->input[sp->i]) == quote_type)
		{
			while (sp->i < sp->len)
			{
				if (is_white_space(sp->input[sp->i]))
					return ;
				else if (check_operator(sp->input[sp->i], 0))
					return ;
				add_char_to_buff(sp);
			}
			return ;
		}
		add_char_to_buff(sp);
	}
}
