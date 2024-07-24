/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/16 11:15:41 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/07/24 18:50:40 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ! issue: vector returns arg twice per arg
// static bool expand_arg(char **env, char *arg, size_t i, t_shell *shell, t_vec *vec)
// {
//     char *key = NULL;
//     char *val = NULL;
//     char *result = NULL;
//     char *new_key = NULL;
//     char *new_result = NULL;
// 	// ! Norm: Too many variables declarations in a function, 5 max

// 	// If arg is one char
// 	if (ft_strlen(arg) == 1)
// 	{
// 		ft_vec_push(vec, arg[0]);
// 		return (SUCCESS);
// 	}

// 	// Get KEY + VAL
// 	arg = skip_multiple_expand_chars(arg, i + 1, shell);
// 	key = get_env_key(arg, i, shell);
// 	// ft_sleep(PROCESS_SLEEP_TIME);
// 	val = get_value_for_key(env, key, shell);

// 	// If env key is expand char
// 	if (key[0] == '?')
// 	{
// 		result = expand_exit_code(arg, key, i, shell);
// 		ft_vec_push_str(vec, result);		
// 		free (result);
// 		free (val);
// 		return (SUCCESS);
// 	}

// 	// Append dollar sign to key
// 	if (key[0] != EXPAND_CHAR)
// 		new_key = ft_strjoin("$", key);
// 	else
// 		new_key = ft_strdup(key);
// 	free(key);

// 	// Romove key from arg
// 	result = ft_str_remove(arg, new_key);
// 	free (new_key);

// 	// If no value exists for this key
// 	if (val == NULL)
// 	{
// 		ft_vec_push_str(vec, result);
// 		free (result);
// 		return (SUCCESS);
// 	}

// 	// Insert the value
// 	if (result)
// 	{
// 		if (val)
// 			new_result = ft_str_insert(result, val, i);
// 		free (result);
// 	}
// 	free (val);

// 	// Result
// 	ft_vec_push_str(vec, new_result);
// 	free (new_result);
// 	return (SUCCESS);
// }

// bool	will_expand(char **env, char *arg, t_shell *shell, t_vec *vec)
// {
// 	size_t	i;
// 	int		expand_count;
// 	int		expanded_count;

// 	expanded_count = 0;
// 	expand_count = count_expand(arg);
// 	if (expand_count == 0)
// 		return (SUCCESS);
// 	i = 0;
// 	while (arg[i])
// 	{
// 		if (expanded_count == expand_count)
// 			break ;
// 		if (arg[i] == EXPAND_CHAR)
// 		{
// 			if (expand_arg(env, arg, i, shell, vec) == false)
// 				return (FAILURE);
// 			expanded_count++;
// 			i = 0;
// 			continue ;
// 		}
// 		i++;
// 	}
// 	return (SUCCESS);
// }
 
static bool	expand_arg(char **env, char *arg, t_shell *shell, t_vec *vec, size_t *i)
{
	char	*key;
	char	*value;

	if (ft_strlen(arg) == 1)
		return (ft_vec_push(vec, arg[0]), SUCCESS);
	key = get_env_key(arg, *i, shell);
	if (key == NULL)
		return (FAILURE);
	if (key[0] == '?')
		return (expand_exit_code(vec, shell) ,SUCCESS);
	value = get_value_for_key(env, key, shell);
	if (value == NULL)
	{
		if (!ft_vec_push(vec, ' ')) // ! return space/null to vector if no value
			return (show_error_message(E_MALLOC, shell, "", X_FAILURE), FAILURE);
		return (free(key), SUCCESS); 
	}
	free(key);
	if (!ft_vec_push_str(vec, value))
		return (show_error_message(E_MALLOC, shell, "", X_FAILURE), FAILURE);
	free (value);
	return (SUCCESS);
}

bool	will_expand(char **env, char *arg, t_shell *shell, t_vec *vec)
{
	size_t	i;
	int		expand_count;
	int		expanded_count;

	expanded_count = 0;
	expand_count = count_expand(arg);
	if (expand_count == 0)
		return (SUCCESS);
	i = 0;
	while (arg[i])
	{
		if (expanded_count == expand_count)
			break ;
		if (arg[i] == EXPAND_CHAR)
		{
			if (expand_arg(env, arg, shell, vec, &i) == false)
				return (FAILURE);
			expanded_count++;
			i = 0; // ! add length of key to loop
			continue ;
		}
		if (!is_quote(arg[i]))
			if (!ft_vec_push(vec, arg[i]))
				return (show_error_message(E_MALLOC, shell, "", X_FAILURE), FAILURE);
		i++;
	}
	return (SUCCESS);
}

// ! tasks:
// TODO implement skip multiple expand char
// TODO echo "hello $USER$TERM" (expand multiple env)
// 		! issue is probably the way arg[i] is looped
// TODO str insert after last expansion is missing -> echo "hello $USER hello"
// TODO when no valid key value, print space/nothing to vector
// TODO commenting strip quote @ double quote works for D_Q expand, but for non expand incorrect output
// * single quote expand / stripping quotes work with no leaks
