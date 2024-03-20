/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   buffer_quote.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 21:58:11 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/16 10:07:49 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_quote(char c)
{
	if (c == D_QUOTE_CHAR)
		return (c);
	else if (c == S_QUOTE_CHAR)
		return (c);
	return (0);
}

// TODO remove quote char
void	add_char_to_buff(t_split *sp)
{
	sp->buffer[sp->i_buff] = sp->input[sp->i];
	sp->i_buff++;
	sp->i++;
}

void	buffer_quote(t_split *sp, int quote_type)
{
	add_char_to_buff(sp);
	while (sp->i <= sp->len)
	{
		if (is_quote(sp->input[sp->i]) == quote_type)
		{
			add_char_to_buff(sp);
			return ;
		}
		add_char_to_buff(sp);
	}
}

// cat "this file" and "another file"
// test 'this "hard quote"'
// test "this ugly" "command" >>>with many things >> that 'can go wrong'
