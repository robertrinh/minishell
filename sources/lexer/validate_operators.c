/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_operators.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/10 16:39:24 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/13 15:45:14 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	validate_pipe_operators(char *input, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if (input[i] == '|')
		{
			if (i + 1 < len)
			{
				if (input[i + 1] == '|' || input[i + 1] == '\0')
					return (false);
			}
		}
		i++;
	}
	return (true);
}

static bool	validate_redirect_operators(char *input, int len)
{
	int		i;
	int		subsequent_count;

	i = 0;
	subsequent_count = 0;
	while (i < len)
	{
		if (ft_strchr(REDIRECTS, input[i]))
		{
			subsequent_count++;
			if (subsequent_count == 3)
				return (false);
		}
		else
			subsequent_count = 0;
		i++;
	}
	return (true);
}

t_validation	validate_operators(char *input)
{
	int		len;

	len = ft_strlen(input);
	if (validate_pipe_operators(input, len) == false)
		return (FAILURE);
	if (validate_redirect_operators(input, len) == false)
		return (FAILURE);
	return (SUCCESS);
}
