/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_env_key.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/29 22:10:43 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/27 14:39:12 by qtrinh        ########   odam.nl         */
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

char	*skip_multiple_expand_chars(char *arg, size_t i, t_shell *shell)
{
	int		j;
	int		k;
	char	*buffer;

	j = i;
	k = 0;
	buffer = safe_malloc(sizeof(char *) * ft_strlen(arg), shell);
	if (arg[j] == EXPAND_CHAR)
	{
		while (arg[j])
		{
			if (arg[j] != EXPAND_CHAR)
			{
				buffer[k] = '\0';
				arg = ft_str_remove(arg, buffer);
				free (buffer);
				return (arg);
			}
			buffer[k] = arg[j];
			k++;
			j++;
		}
	}
	free(buffer);
	return (arg);
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
