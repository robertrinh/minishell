/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_handle_export_args_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:51:23 by qbeukelm          #+#    #+#             */
/*   Updated: 2024/09/02 14:01:48 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#define EXPORT_STRING "export"

void	did_add_spaces(size_t *i, size_t space_count, char *buffer)
{
	if (space_count)
	{
		while (*i < space_count)
		{
			buffer[*i] = ' ';
			(*i)++;
		}
	}
}
