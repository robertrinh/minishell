/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_finish_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/23 16:15:41 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/27 13:13:41 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_token(t_token *token)
{
	if (token == NULL)
		return ;
	free(token);
	token = NULL;
}

void	free_tokens(t_token *token)
{
	t_token	*next;

	next = NULL;
	if (token == NULL)
		return ;
	while (token)
	{
		next = token->next;
		free_token(token);
		token = next;
	}
}

void	free_split(t_split *split)
{
	if (split)
	{
		free_2d_array(split->strings);
		split->strings = NULL;
	}
	free(split);
	split = NULL;
}

void	free_2d_array(char **array)
{
	int	i;

	if (array)
	{
		i = 0;
		while (array[i])
		{
			free(array[i]);
			array[i] = NULL;
			i++;
		}
		free(array);
	}
}
