/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/27 12:23:45 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/08/01 17:50:23 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	index_next_quote(t_split *sp, int quote_type)
{
	while (sp->i < sp->len)
	{
		if (is_quote(sp->input[sp->i]) == quote_type)
		{
			sp->i++;
			return (SUCCESS);
		}
		sp->i++;
	}
	return (FAILURE);
}

static void	process_substring(t_split *sp)
{
	int	op_check;

	while (sp->i < sp->len)
	{
		op_check = check_operator(sp->input[sp->i], sp->input[sp->i + 1]);
		if (is_white_space(sp->input[sp->i]))
			break ;
		if (op_check == 2)
		{
			sp->i += 2;
			sp->count++;
			return ;
		}
		else if (op_check == 1)
		{
			sp->i++;
			sp->count++;
			return ;
		}
		else if (is_quote(sp->input[sp->i]))
			index_next_quote(sp, is_quote(sp->input[sp->i]));
		else
			sp->i++;
	}
}

static int	count_substrings(t_split *sp)
{
	while (sp->i < sp->len)
	{
		sp->i = skip_whitespace(sp);
		if (sp->i >= sp->len)
			break ;
		sp->i_check = sp->i;
		process_substring(sp);
		if (sp->i > sp->i_check)
			sp->count++;
	}
	return (sp->count);
}

t_split	*split(t_shell *shell)
{
	t_split	*split;

	split = safe_malloc(sizeof(t_split), shell);
	split = init_split(shell, split);
	split->count = count_substrings(split);
	split->strings = NULL;
	split->strings = safe_calloc(sizeof(char *), (split->count + 1), shell);
	if (split->strings == NULL)
	{
		free_split(split);
		show_error(E_MALLOC, shell, "split", X_FAILURE);
		return (NULL);
	}
	split->strings = allocate_strings_split(split, shell);
	if (split->strings == NULL)
		return (NULL);
	return (split);
}
