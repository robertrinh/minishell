/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/16 11:15:41 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/15 16:22:38 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_utils	*init_env_utils(char **env, char *arg, size_t i)
{
	t_env_utils		*env_utils;

	env_utils = safe_malloc(sizeof(t_env_utils));
	env_utils->key = get_env_key(arg, i);
	ft_sleep(PROCESS_SLEEP_TIME);
	env_utils->value = get_value_for_key(env, env_utils->key);
	return (env_utils);
}

static char	*expand_arg(char **env, char *arg, size_t i)
{
	t_env_utils		*env_utils;

	if (ft_strlen(arg) == 1)
		return (arg);
	env_utils = NULL;
	env_utils = init_env_utils(env, arg, i);
	if (env_utils->key[0] == '?')
	{
		arg = expand_exit_code(arg, env_utils->key, i);
		return (arg);
	}
	if (env_utils->key[0] != EXPAND_CHAR)
		env_utils->key = ft_strjoin("$", env_utils->key);

	if (arg && env_utils->value && is_arg_key(arg, env_utils->key))
	{
		arg = env_utils->value;
		free_env_values(env_utils->key, NULL, env_utils);
		return (arg);
	}
	arg = ft_str_remove(arg, env_utils->key);
	if (arg && env_utils->value)
		arg = ft_str_insert(arg, env_utils->value, i);
	free_env_values(env_utils->key, env_utils->value, env_utils);
	return (arg);
}

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
