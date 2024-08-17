/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_handle_export_args.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 21:18:16 by quentin           #+#    #+#             */
/*   Updated: 2024/08/17 21:51:19 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
# define EXPORT_STRING "export"

bool	interpret_whitespace(t_shell *shell, t_split *sp)
{
	sp->i_before = sp->i;
	sp->i = skip_whitespace(sp);
	sp->i_buff = 0;
	if (sp->input[sp->i] == '|')
		sp->is_export = false;
	sp->space_count = sp->i - sp->i_before;
	return (SUCCESS);
}

bool is_export(char *buffer)
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
	char		*buffer;
	size_t		i = 0;
	size_t		j = 0;

	if (is_export(sp->buffer))
		return (FAILURE);
	buffer = safe_malloc((sizeof(char *)) \
        * (ft_strlen(sp->buffer) + space_count + 2), shell);
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
	free(sp->buffer);
	return (sp->buffer = buffer);
}

/*
    Adds spaces back into args following export.
    Split tries to skip these spaces.
*/
bool should_handle_export(t_shell *shell, t_split *sp)
{
	if (is_export(sp->buffer))
		sp->is_export = true;
	if (sp->is_export)
	{
		sp->curr_export_arg++;
		if (sp->curr_export_arg > 2)
			will_add_spaces(shell, sp, sp->space_count);
	}
	else
		sp->buffer[sp->i_buff] = 0;
	return (SUCCESS);
}
