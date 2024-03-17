/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/16 11:15:41 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/17 16:37:30 by quentinbeuk   ########   odam.nl         */
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

static char	*expand_arg(char **env, char *arg, int i)
{
	char	*key;
	char	*value;

	key = get_env_key(arg, i);
	value = get_value_for_key(env, key);
	if (key == NULL || value == NULL)
		return (0);

	// TODO protect str_remove() & str_incert()
	key = ft_strjoin("$", key);
	arg = ft_str_remove(arg, key);
	if (arg)
		arg = ft_str_incert(arg, value, i);

	free (key);
	free (value);
	return (arg);
}

// !	echo "hello $USER$TERM more "
// !	echo "hello $USER more"
// !	echo hello$USER
char	*will_expand(char **env, char *arg)
{
	int		i;

	if (ft_strchr(arg, EXPAND_CHAR) == NULL)
		return (arg);
	
	i = 0;
	while (arg[i])
	{
		if (arg[i] == EXPAND_CHAR)
		{
			arg = expand_arg(env, arg, i);
			i = 0;
			continue ;
		}
		i++;
	}
	return (arg);
}
