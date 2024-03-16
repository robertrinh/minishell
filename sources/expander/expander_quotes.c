/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_quotes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/16 11:15:41 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/16 11:20:36 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_env_key(char *arg, int i)
{
	int		j;
	char	*key;

	i += 1;
	j = 0;
	key = safe_malloc(sizeof(char *) * ft_strlen(arg));
	while (arg[i])
	{
		if (ft_isspace(arg[i]))
			return (key);
		key[j] = arg[i];
		j++;
		i++;
	}
	return (key);
}

static int		expand_quote(char *arg, int i)
{
	char	*key;

	key = get_env_key(arg, i);
	if (key == NULL)
		return (0);



	return (0);
}

void	strip_quote_chars(char *arg)
{
	int i;
	int	len;

	i = 0;
	len = ft_strlen(arg);
	while (i < len)
	{
		arg[i] = arg[i + 1];
		i++;
	}
	arg[len - 2] = '\0';
}

int		will_expand_quotes(char *arg)
{
	int		i;

	if (ft_strchr(arg, EXPAND_CHAR) == NULL)
		return (0);
	
	i = 0;
	while (arg[i])
	{
		if (arg[i] == EXPAND_CHAR)
			expand_quote(arg, i);
		i++;
	}
	return (0);
}
