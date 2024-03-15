/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 21:19:19 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/14 17:23:34 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Given starting index, returns the count of remaining lines in env
*/
int		count_lines_from(char **env, int index)
{
	int		count;

	count = 0;
	while (env[index])
	{
		count++;
		index++;
	}
	return (count);
}

/*
	Returns the size of the **envp in bytes
*/
size_t	env_size(char **env)
{
	size_t		env_size;
    char		**temp;

	env_size = 0;
	temp = env;
    while (*temp != NULL) {
        env_size += strlen(*temp) + 1;
        temp++;
    }
	return (env_size);
}

/*
	Returns the line index for a given env key,
	and -1 if key is not present in env.
*/
int	index_for_env_key(char **input_env, char *key)
{
	int		i;
	char	**env;

	i = 0;
	env = input_env;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, ft_strlen(key)) == 0)
		{
			if (env[i][ft_strlen(key)] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}
