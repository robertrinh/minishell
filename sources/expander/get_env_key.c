/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_env_key.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/29 22:10:43 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/07/25 17:00:07 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_end_env_key(char c)
{
	if (ft_isspace(c))
		return (true);
	else if (c == D_QUOTE_CHAR || c == S_QUOTE_CHAR)
		return (true);
	else if (c == EXPAND_CHAR)
		return (true);
	return (false);
}

char	*get_env_key(char *arg, size_t i, t_shell *shell)
{
	int		j;
	char	*key;

	i += 1;
	if (arg[i] == EXIT_CODE_CHAR)
		return ("?");
	if (ft_strlen(arg) == i + 1)
	{
		key = safe_strdup_from(arg, i, shell);
		key = ft_str_remove_char(key, 0, EXPAND_CHAR);
		return (key);
	}
	j = 0;
	key = safe_malloc(sizeof(char *) * ft_strlen(arg) + 1, shell);
	while (arg[i])
	{
		if (is_end_env_key(arg[i]))
			break ;
		key[j] = arg[i];
		j++;
		i++;
	}
	key[j] = '\0';
	return (key);
}
