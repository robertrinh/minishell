/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:15:41 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/09/02 14:02:20 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	should_push_one_char(char *arg, t_vec *vec, size_t *i)
{
	(*i) += 1;
	return (ft_vec_push(vec, arg[*i]), SUCCESS);
}

static bool	expand_arg(char *arg, t_shell *shell, t_vec *vec, size_t *i)
{
	char	*key;
	char	*value;

	if (ft_strlen(arg) == 1)
		return (should_push_one_char(arg, vec, i));
	key = get_env_key(arg, *i, shell);
	if (key[0] == '?')
	{
		(*i) += 2;
		return (expand_exit_code(vec, shell), SUCCESS);
	}
	value = get_value_for_key(shell->envp, key, shell);
	if (value == NULL)
	{
		(*i) += ft_strlen(key) + 1;
		return (free(key), SUCCESS);
	}
	(*i) += ft_strlen(key) + 1;
	free(key);
	if (!ft_vec_push_str(vec, value))
		return (show_error(E_MALLOC, shell, "", X_FAILURE), FAILURE);
	free (value);
	return (SUCCESS);
}

bool	will_expand(char *arg, t_shell *shell, t_vec *vec)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(arg);
	while (i < len)
	{
		if (arg[i] == D_QUOTE_CHAR)
			i++;
		if (arg[i] == EXPAND_CHAR)
		{
			skip_multiple_expand_chars(arg, &i);
			if (expand_arg(arg, shell, vec, &i) == false)
				return (FAILURE);
			continue ;
		}
		if (!ft_vec_push(vec, arg[i]))
			return (show_error(E_MALLOC, shell, "", X_FAILURE), FAILURE);
		i++;
	}
	return (SUCCESS);
}
