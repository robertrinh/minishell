/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 21:19:19 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/21 17:03:54 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*buffer_env_value(char *env_row, char *key, int i, t_shell *shell)
{
	char	*value;
	int		j;
	int		len;

	i += 1;
	j = 0;
	len = ft_strlen(env_row) - ft_strlen(key) + 1;
	value = safe_malloc(sizeof(char *) * len, shell);
	while (env_row[i])
	{
		if (ft_isspace(env_row[i]))
			break ;
		value[j] = env_row[i];
		j++;
		i++;
	}
	value[j] = '\0';
	return (value);
}

/*
	Given key e.g. 'KEY=value', get_value_for_key() returns the string value
	for the corresponding env key.
*/
char	*get_value_for_key(char **env, char *key, t_shell *shell)
{
	int		row_index;
	int		i;

	row_index = index_for_env_key(env, key);
	if (row_index == -1)
		return (NULL);
	i = 0;
	while (env[row_index][i])
	{
		if (env[row_index][i] == '=')
			return (buffer_env_value(env[row_index], key, i, shell));
		i++;
	}
	return (NULL);
}

/*
	Given starting index, returns the count of remaining lines in env
*/
int	count_lines_from(char **env, int index)
{
	int	count;

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
	size_t	env_size;
	char	**temp;

	if (env == NULL)
		return (0);
	env_size = 0;
	temp = env;
	while (*temp != NULL)
	{
		env_size += ft_strlen(*temp) + 1;
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
