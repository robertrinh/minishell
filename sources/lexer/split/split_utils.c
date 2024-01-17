/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 15:59:08 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/01/17 16:07:56 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	is_white_space(char c)
{
	if (c >= 9 && c <= 13 || c == 32)
		return (true);
	return (false);
}

int	skip_whitespace(t_split *sp)
{
	while (sp->i < sp->len)
	{
		if (is_white_space(sp->input[sp->i]) == false)
			break ;
		sp->i++;
	}
	return (sp->i);
}

static bool	is_double_operator(char c1, char c2)
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
