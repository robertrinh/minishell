/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_strings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 13:01:10 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/08/17 15:43:03 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
# define EXPORT_STRING "export"

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

static bool is_export(char *buffer)
{
	size_t		export_len;

	export_len = ft_strlen(EXPORT_STRING);
	if (ft_strlen(buffer) != export_len)
		return (false);
	if (ft_strncmp(buffer, EXPORT_STRING, export_len) == 0)
		return (true);

	return (false);
}

bool will_add_spaces(t_shell *shell, t_split *sp, size_t space_count)
{
	char	*buffer;
	size_t		i = 0;
	size_t		j = 0;

	if (is_export(sp->buffer))
		return (FAILURE);

	// 1. Create new string
	buffer = safe_malloc((sizeof(char *)) * (ft_strlen(sp->buffer) + space_count + 2), shell);
	if (space_count)
	{
		while (i < space_count)
		{
			buffer[i] = ' ';
			i++;
		}
	}
	while (j < ft_strlen(sp->buffer))
	{
		buffer[i] = sp->buffer[j];
		i++;
		j++;
	}
	buffer[j + i - 1] = '\0';

	// 2. Free old buffer
	free(sp->buffer);

	// 3. Insert new buffer
	sp->buffer = buffer;

	return (SUCCESS);
}

char	**allocate_strings_split(t_split *sp, t_shell *shell)
{
	size_t		i_before;
	size_t		space_count;
	bool	is_export_bool;

	i_before = 0;
	space_count = 0;
	is_export_bool = false;

	sp->i = 0;
	while (sp->i < sp->len)
	{
		sp->buffer = safe_calloc(sizeof(char), BUFF_SIZE, shell);
		if (sp->buffer == NULL)
		{
			free_split(sp);
			show_error(E_MALLOC, shell, "split", X_FAILURE);
			return (NULL);
		}
		

		i_before = sp->i;
		sp->i = skip_whitespace(sp);
		sp->i_buff = 0;
		if (sp->input[sp->i] == '|')
			is_export_bool = false;

		space_count = sp->i - i_before;
		
		sp = handle_substrings(sp, shell);
		if (sp == NULL)
			return (NULL);
		
		// ! Check for export
		if (is_export(sp->buffer))
			is_export_bool = true;

		if (is_export_bool)
			will_add_spaces(shell, sp, space_count);
		else
			sp->buffer[sp->i_buff] = 0;
		
		sp->strings = allocate_substrings(sp);
	}
	sp->strings[sp->i_str] = 0;
	return (sp->strings);
}
