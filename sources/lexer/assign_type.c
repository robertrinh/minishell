/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:27:34 by qbeukelm          #+#    #+#             */
/*   Updated: 2024/01/19 16:12:53 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	contains_redirect(char *value)
{
	int	i;

	i = 0;
	while (REDIRECTS[i])
	{
		if (ft_strchr(value, REDIRECTS[i]))
			return (true);
		i++;
	}
	return (false);
}

t_token_type	assign_type(char *value)
{
	if (contains_redirect(value))
		return (REDIRECT);
	else if (ft_strchr(value, '|'))
		return (PIPE);
	return (NONE);
}
