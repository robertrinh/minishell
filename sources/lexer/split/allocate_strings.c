/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   allocate_strings.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/07 13:01:10 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/22 01:56:53 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	clear_buffer(t_split *sp)
{
	int	i;

	i = 0;
	while (i < BUFF_SIZE)
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

bool	check_operators_substring(t_split *sp)
{
	if (check_operator(sp->input[sp->i], sp->input[sp->i + 1]) == 2)
	{
		if (sp->i_buff)
			return (false);
		sp->buffer[sp->i_buff] = sp->input[sp->i];
		sp->buffer[sp->i_buff + 1] = sp->input[sp->i + 1];
		sp->i += 2;
		sp->i_buff += 2;
		return (false);
	}
	else if (check_operator(sp->input[sp->i], sp->input[sp->i + 1]) == 1)
	{
		if (sp->i_buff)
			return (false);
		sp->buffer[sp->i_buff] = sp->input[sp->i];
		sp->i++;
		sp->i_buff++;
		return (false);
	}
	return (true);
}

t_split	*handle_substrings(t_split *sp)
{
	while (sp->i < sp->len)
	{
		if (is_quote(sp->input[sp->i]) != 0)
		{
			buffer_quote(sp, is_quote(sp->input[sp->i]));
			break ;
		}
		if (is_white_space(sp->input[sp->i])
			|| check_operators_substring(sp) == false)
			break ;
		sp->buffer[sp->i_buff] = sp->input[sp->i];
		sp->i++;
		sp->i_buff++;
		if (sp->i >= BUFF_SIZE - 2 || sp->i_buff >= BUFF_SIZE - 2)
		{
			show_error_message(E_OVERFLOW, C_RED, "", X_FAILURE);
			return (NULL);
		}
	}
	return (sp);
}

char	**allocate_strings_split(t_split *sp)
{
	sp->i = 0;
	while (sp->i < sp->len)
	{
		sp->i = skip_whitespace(sp);
		sp->i_buff = 0;
		sp = handle_substrings(sp);
		if (sp == NULL)
			return (NULL);
		sp->buffer[sp->i_buff] = 0;
		sp->strings = allocate_substrings(sp);
	}
	sp->strings[sp->i_str] = 0;
	return (sp->strings);
}
