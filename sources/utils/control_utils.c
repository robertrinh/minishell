/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   control_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/29 21:56:32 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/04/04 16:46:46 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_sleep(size_t count)
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
