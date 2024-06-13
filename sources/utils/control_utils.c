/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   control_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/29 21:56:32 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/13 16:35:20 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_sleep(size_t count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (j <= count)
	{
		i = 0;
		while (i <= count)
			i++;
		j++;
	}
	return ;
}
