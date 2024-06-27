/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/16 11:15:41 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/27 14:49:30 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft/lib_vector/vector.h"

static char *expand_arg(char **env, char *arg, size_t i, t_shell *shell)
{
	t_vec	vec_val;
    char *key = NULL;
    char *val = NULL;
    char *result = NULL;
    char *new_key = NULL;
    char *new_result = NULL;
	// ! Norm: Too many variables declarations in a function, 5 max
	
	if (ft_vec_init(&vec_val, ft_strlen(arg)) == false)
		return (NULL);

	// If arg is one char
	if (ft_strlen(arg) == 1)
	{
		ft_vec_push(&vec_val, arg[0]);
		return (ft_vec_to_str(&vec_val));
	}

	// Get KEY + VAL
	arg = skip_multiple_expand_chars(arg, i + 1, shell);
	key = get_env_key(arg, i, shell);
	// ft_sleep(PROCESS_SLEEP_TIME);
	val = get_value_for_key(env, key, shell);

	// If env key is expand char
	if (key[0] == '?')
	{
		result = expand_exit_code(arg, key, i, shell);
		ft_vec_push_str(&vec_val, result);		
		free (result);
		free (val);
		return (ft_vec_to_str(&vec_val));
	}

	// Append dollar sign to key
	if (key[0] != EXPAND_CHAR)
		new_key = ft_strjoin("$", key);
	else
		new_key = ft_strdup(key);
	free(key);

	// Romove key from arg
	result = ft_str_remove(arg, new_key);
	free (new_key);

	// If no value exists for this key
	if (val == NULL)
	{
		ft_vec_push_str(&vec_val, result);
		free (result);
		return (ft_vec_to_str(&vec_val));
	}

	// Insert the value
	if (result)
	{
		if (val)
			new_result = ft_str_insert(result, val, i);
		free (result);
	}
	free (val);

	// Result
	ft_vec_push_str(&vec_val, new_result);
	free (new_result);
	return (ft_vec_to_str(&vec_val));
}

char	*will_expand(char **env, char *arg, t_shell *shell)
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
			arg = expand_arg(env, arg, i, shell);
			expanded_count++;
			i = 0;
			continue ;
		}
		i++;
	}
	return (arg);
}
