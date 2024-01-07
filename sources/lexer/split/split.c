/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/05 14:17:27 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/01/07 13:14:24 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	skip_whitespace(t_split *sp)
{
	while (sp->i < sp->len)
	{
		if (sp->input[sp->i] != 32)
			break ;
		sp->i++;
	}
	return (sp->i);
}

static bool is_double_operator(char c1, char c2)
{
	if (ft_strchr(REDIRECTS, c1) && ft_strchr(REDIRECTS, c2))
	{
		if (c1 == c2)
			return (true);
	}
	return (false);
}

int	check_operator(char c1, char c2)
{
	if (ft_strchr(OPERATORS, c1) == 0)
		return (0);
	if (is_double_operator(c1, c2))
		return (2);
	if (ft_strchr(OPERATORS, c1))
		return (1);
	return (0);
}

static	int	count_substrings(t_split *sp)
{
	while (sp->i < sp->len)
	{
		sp->i = skip_whitespace(sp);
		sp->i_check = sp->i;
		while (sp->i < sp->len)
		{
			if (sp->input[sp->i] == 32)
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
			sp->i++;
		}
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
	printf("Substring count: %d\n", split->count);

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
