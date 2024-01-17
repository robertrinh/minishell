/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/05 14:17:27 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/01/17 16:07:07 by qtrinh        ########   odam.nl         */
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

	split = malloc(sizeof(t_split));
	if (split == NULL)
	{
		// TODO clean_exit()
	}
	split = init_split(shell, split);

	// 1. Count substrings
	split->count = count_substrings(split);

	// 2. Malloc substring for count
	split->strings = ft_calloc(sizeof(char *), (split->count + 1));
	if (split->strings == NULL)
	{
		// TODO clean_exit()
	}

	// 3. Assign strings
	split->strings = allocate_strings(split);

	// 4. Free split struct
	return (split->strings);
}
