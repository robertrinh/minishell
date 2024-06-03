/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/23 21:54:16 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/01 16:20:36 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void free_env_values(char *key, char *value, t_env_utils *env_utils)
{
	if (key != NULL)
		free (key);
	if (value != NULL)
		free (value);
	if (env_utils != NULL)
		free (env_utils);
}

int	count_expand(char *arg)
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

bool is_arg_key(char *arg, char *key)
{
	if (ft_strncmp(arg, key, (ft_strlen(key) + ft_strlen(arg)))  == 0)
		return (true);
	return (false);
}

char *expand_exit_code(char *arg, char *key, char *val, \
	size_t i, t_env_utils *env_utils)
{
	char	*exit_code_string;

	key = safe_strjoin("$", key);
	arg = ft_str_remove(arg, key); // ! key/arg = NULL
	exit_code_string = ft_itoa(g_exit_code);
	arg = ft_str_insert(arg, exit_code_string, i);
	// free (exit_code_string);
	free_env_values(key, val, env_utils);
	return (arg);
}
