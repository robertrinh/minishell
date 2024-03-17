/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/16 11:15:41 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/17 10:09:11 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_env_key(char *arg, int i)
{
	int		j;
	char	*key;

	i += 1;
	j = 0;
	key = safe_malloc(sizeof(char *) * ft_strlen(arg));
	while (arg[i])
	{
		if (ft_isspace(arg[i]) || arg[i] == EXPAND_CHAR)
			return (key);
		key[j] = arg[i];
		j++;
		i++;
	}
	return (key);
}

static int	expand_arg(char **env, char *arg, int i)
{
	char	*key;

	key = get_env_key(arg, i);
	if (key == NULL)
		return (0);

	// TODO free Key & Value
	printf("key: %s\n", key);
	printf("value: %s\n", get_value_for_key(env, key));

	return (0);
}

int		will_expand(char **env, char *arg)
{
	int		i;

	if (ft_strchr(arg, EXPAND_CHAR) == NULL)
		return (0);
	
	i = 0;
	while (arg[i])
	{
		if (arg[i] == EXPAND_CHAR)
			expand_arg(env, arg, i);
		i++;
	}
	return (0);
}
