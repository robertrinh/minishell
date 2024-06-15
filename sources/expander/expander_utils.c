/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/23 21:54:16 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/15 16:21:14 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft/lib_vector/vector.h"

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

char *expand_exit_code(char *arg, char *key, size_t i)
{
	char	*exit_code_string;
	char	*leading_substr;
	char	*trailing_substr;
	t_vec	vec_arg;

	key = safe_strjoin("$", key);
	arg = ft_str_remove(arg, key);
	exit_code_string = ft_itoa(g_exit_code);

	leading_substr = ft_substr(arg, 0, i);
	trailing_substr = ft_substr(arg, i, ft_strlen(arg));

	ft_vec_init(&vec_arg, ft_strlen(arg) + ft_strlen(exit_code_string) + 1);
	ft_vec_push_str(&vec_arg, leading_substr);
	ft_vec_push_str(&vec_arg, exit_code_string);
	ft_vec_push_str(&vec_arg, trailing_substr);
	
	free (key);
	free (exit_code_string);
	free (leading_substr);
	free (trailing_substr);

	return (ft_get_str(&vec_arg));
}
