/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/05 14:17:27 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/04/04 21:06:22 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	index_next_quote(t_split *sp, int quote_type)
{
	while (sp->i < sp->len)
	{
		if (is_quote(sp->input[sp->i]) == quote_type)
			return (SUCCESS);
		sp->i++;
	}
	return (FAILURE);
}

static void	process_substring(t_split *sp)
{
	while (sp->i < sp->len) // Check last char
	{
		if (is_white_space(sp->input[sp->i]))
			break ;
		if (check_operator(sp->input[sp->i], sp->input[sp->i + 1]))
		{
			if (check_operator(sp->input[sp->i], sp->input[sp->i + 1]) == 2)
			{
				sp->i += check_operator(sp->input[sp->i], sp->input[sp->i + 1]);
				sp->count++;
				break ;
			}
			sp->count++;
		}
		else if (is_quote(sp->input[sp->i]))
			index_next_quote(sp, is_quote(sp->input[sp->i]));
		sp->i++;
	}
}

static int	count_substrings(t_split *sp)
{
	while (sp->i < sp->len)
	{
		sp->i = skip_whitespace(sp);
		sp->i_check = sp->i;
		process_substring(sp);
		if (sp->i > sp->i_check)
			sp->count++;
	}
	return (sp->count);
}

char	**split(t_shell *shell)
{
	t_split		*split;
	char		**split_string;

	split = safe_malloc(sizeof(t_split));
	split = init_split(shell, split);
	split->count = count_substrings(split);
	split->strings = ft_calloc(sizeof(char *), (split->count + 1));
	if (split->strings == NULL)
	{
		// TODO clean_exit()
	}
	split->strings = allocate_strings_split(split);
	split_string = split->strings;
	free(split);
	return (split_string);
}
