/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   post_lexer_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/13 15:46:21 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/06/13 16:23:30 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_special_type(t_token_type type)
{
	if (type == PIPE || type == REDIRECT)
		return (true);
	return (false);
}

t_token	*skip_operators(t_token *current)
{
	while (current)
	{
		if (is_special_type(current->type) == false)
			return (current);
		if (current->next)
			current = current->next;
		else
			return (current);
	}
	return (current);
}

t_token	*assign_argfile_args(t_token *current)
{
	current->type = ARGFILE;
	while (current)
	{
		if (is_special_type(current->type) == true)
			return (current);
		if (current->type == NONE)
			current->type = ARGUMENT;
		if (current->next)
			current = current->next;
		else
			return (current);
	}
	return (current);
}

t_token	*assign_cmd_arg(t_token *current, int i)
{
	if (current->type == NONE || i == 0)
		current->type = COMMAND;
	else if (current->next)
		current = current->next;
	while (current)
	{
		if (current->type == NONE || i > 0)
		{
			current->type = ARGUMENT;
			if (current->next)
			{
				if (is_special_type(current->type) == true)
					current = current->next;
			}
		}
		if (is_special_type(current->type) == true)
			return (current);
		if (current->next)
			current = current->next;
		else
			return (current);
	}
	return (current);
}
