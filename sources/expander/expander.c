/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/16 11:15:41 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/18 18:03:04 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_env_key(char *arg, int i)
{
	int		j;
	char	*key;

	i += 1;
	j = 0;
	key = safe_malloc(sizeof(char *) * ft_strlen(arg) + 1);
	while (arg[i])
	{
		if (ft_isspace(arg[i]) || arg[i] == EXPAND_CHAR)
			return (key);
		key[j] = arg[i];
		j++;
		i++;
	}
	key[j] = '\0';
	return (key);
}

static char	*expand_arg(char **env, char *arg, int i)
{
	char	*key;
	char	*value;

	key = get_env_key(arg, i);
	value = get_value_for_key(env, key);

	key = ft_strjoin("$", key);
	arg = ft_str_remove(arg, key);

	if (arg && value)
		arg = ft_str_incert(arg, value, i);

	free (key);
	free (value);
	return (arg);
}

static int	count_expand(char *arg)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (arg[i] == EXPAND_CHAR)
			count++;
		i++;
	}
	return (count);
}

// !	echo "hello $USER$TERM more "
// !	echo "hello $USER more"
// !	echo hello$USER
// !	echo "hello $NOT_A_KEY"
// TODO protect str_remove() & str_incert() 
char	*will_expand(char **env, char *arg)
{
	int		i;
	int		expand_count;
	int		expanded_count;

	expanded_count = 0;
	expand_count = count_expand(arg);
	if (expand_count == 0)
		return (arg);
	
	i = 0;
	while (arg[i])
	{
		if (expanded_count == expand_count)
			break ;
		if (arg[i] == EXPAND_CHAR)
		{
			arg = expand_arg(env, arg, i);
			expanded_count++;
			i = 0;
			continue ;
		}
		i++;
	}
	return (arg);
}
