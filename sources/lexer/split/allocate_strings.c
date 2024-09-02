/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_strings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 13:01:10 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/09/02 13:37:36 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	**allocate_substrings(t_split *sp)
{
	if (sp->i_buff > 0)
	{
		sp->strings[sp->i_str] = ft_strdup(sp->buffer);
		if (sp->strings[sp->i_str] == NULL)
			return (free_split(sp), NULL);
		sp->i_str++;
	}
	free(sp->buffer);
	return (sp->strings);
}

static bool	check_operators_substring(t_split *sp)
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

static t_split	*handle_substrings(t_split *sp, t_shell *shell)
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
			show_error(E_OVERFLOW, shell, "", X_FAILURE);
			return (NULL);
		}
	}
	return (sp);
}

static bool	split_allocate_buffer(t_shell *shell, t_split *sp)
{
	sp->buffer = safe_calloc(sizeof(char), BUFF_SIZE, shell);
	if (sp->buffer == NULL)
	{
		free_split(sp);
		show_error(E_MALLOC, shell, "split", X_FAILURE);
		return (false);
	}
	return (true);
}

char	**allocate_strings_split(t_split *sp, t_shell *shell)
{
	sp->i = 0;
	while (sp->i < sp->len)
	{
		if (split_allocate_buffer(shell, sp) == false)
			return (NULL);
		if (interpret_whitespace(sp) == FAILURE)
			return (NULL);
		sp = handle_substrings(sp, shell);
		if (sp == NULL)
			return (NULL);
		if (has_multiple_export_delimiters(sp) == false)
			if (should_handle_export(shell, sp) == FAILURE)
				return (NULL);
		sp->strings = allocate_substrings(sp);
	}
	sp->strings[sp->i_str] = 0;
	return (sp->strings);
}
