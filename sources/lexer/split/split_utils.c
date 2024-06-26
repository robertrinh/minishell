/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 15:59:08 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/06/22 01:59:56 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_split	*init_split(t_shell *shell, t_split *split)
{
	split->input = safe_strdup(shell->input);
	split->len = ft_strlen(shell->input);
	split->i = 0;
	split->i_check = 0;
	split->count = 0;
	split->i_buff = 0;
	split->i_str = 0;
	split->strings = 0;
	return (split);
}

bool	is_white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
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
