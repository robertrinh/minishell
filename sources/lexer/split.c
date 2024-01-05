/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:17:27 by qbeukelm          #+#    #+#             */
/*   Updated: 2024/01/05 17:38:06 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	skip_leading_whitespace(char const *input, int len, int i)
{
	while (i < len)
	{
		if (input[i] != 32)
			break ;
		i++;
	}
	return (i);
}

static bool is_double_operator(char c1, char c2)
{
	char	redirect[3] = "<>";

	if (ft_strchr(redirect, c1) && ft_strchr(redirect, c2))
	{
		if (c1 == c2)
			return (true);
	}
	return (false);
}

static int	check_operator(char c1, char c2)
{
	char	operators[6] = "<>|";

	if (ft_strchr(operators, c1) == 0)
		return (0);
	if (is_double_operator(c1, c2))
		return (2);
	if (ft_strchr(operators, c1))
		return (1);
	return (0);
}

char	**allocate_substrings(char const *input, int len, char **strings)
{
	//! next time
}

static int count_substrings(char const *input)
{
	int		len;
	int		i;
	int		i_check;
	int		count;

	len = ft_strlen(input);
	i = 0;
	i_check = 0;
	count = 0;
	while (i < len)
	{
		i = skip_leading_whitespace(input, len, i);
		i_check = i;
		while (i < len)
		{
			if (input[i] == 32)
				break ;
			//printf("operators: c1 %c and c2 %c \t result = %d\n", input[i], input[i + 1], check_operator(input[i], input[i + 1]));
			if (check_operator(input[i], input[i + 1]))
			{
				if (check_operator(input[i], input[i + 1]) == 2)
					i += check_operator(input[i], input[i + 1]);
				count++;
			}

			i++;
		}
		if (i > i_check)
			count++;
	}
	return (count);
}

void	split(char const *input)
{
	int	count;
	char	**strings;
	// 1. Count substrings
	count = count_substrings(input);
	printf("count is: %d\n", count_substrings(input));

	// 2. Allocate memory substrings
	strings = ft_calloc(sizeof(char *), (count + 1));
	if (strings == NULL)
	{
		//TODO clean/exit function
	}
	//strings = allocate_substrings

	// 3. Write to substrings

	//TODO rest of split
	//TODO might hardcode -n?
	
	printf("%s\n", input);
}

// first>last