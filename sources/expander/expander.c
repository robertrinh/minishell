/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/16 11:15:41 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/04/11 13:47:02 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static char *expand_exit_code(char *arg, char *key, size_t i)
{
	key = ft_strjoin("$", key);
	arg = ft_str_remove(arg, key);
	arg = ft_str_insert(arg, ft_itoa(g_exit_code), i);
	return (arg);
}

static char	*expand_arg(char **env, char *arg, size_t i)
{
	char	*key;
	char	*value;

	if (ft_strlen(arg) == 1)
		return (arg);

	key = get_env_key(arg, i);
	ft_sleep(5000);
	value = get_value_for_key(env, key);
	if (key[0] == '?')
		return (expand_exit_code(arg, key, i));

	if (key[0] != EXPAND_CHAR)
		key = ft_strjoin("$", key);
	
	if (arg && value)
	{
		if (ft_strncmp(arg, key, (ft_strlen(key) + ft_strlen(arg)))  == 0)
			return (arg = value);
	}

	arg = ft_str_remove(arg, key);

	if (arg && value)
		arg = ft_str_insert(arg, value, i);

	free (value);
	free (key);
	return (arg);
}

// TODO protect str_remove() & str_insert()
// TODO Free key + value at early return
char	*will_expand(char **env, char *arg)
{
	size_t	i;
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
