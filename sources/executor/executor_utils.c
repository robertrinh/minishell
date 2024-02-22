/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 19:43:07 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/02/22 19:43:30 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void print_2d_char(char **arr)
{
	int i = 0;
	while (arr[i])
	{
		printf("2D[%d] %s\n", i, arr[i]);
		i++;
	}
}
