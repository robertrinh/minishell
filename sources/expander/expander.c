/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/16 11:15:41 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/22 16:06:25 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_env_key(char *arg, int i)
{
	int		j;
	char	*key;

	i += 1;
	if (arg[i] == '?')
		return ("?");
	
	if (ft_strlen(arg) == i + 1)
	{
		printf("return [%d] %s\n", i + 1, arg);	
		return (arg);
	}
	
	j = 0;
	key = safe_malloc(sizeof(char *) * ft_strlen(arg) + 1);
	while (arg[i])
	{
		if (ft_isspace(arg[i]) || arg[i] == EXPAND_CHAR)
			return (key);
		key[j] = arg[i];
		j++;
		i++;
	}
	key[j] = '\0';
	return (key);
}

static bool should_add_dollar_sign(char *arg, int i)
{
	while (arg[i])
	{
		if (arg[i] != '$')
			return (true);
		i++;
	}
	return (false);
}

static char	*expand_arg(char **env, char *arg, int i)
{
	char	*key;
	char	*value;

	if (ft_strlen(arg) == 1)
		return (arg);
		
	key = get_env_key(arg, i);
	value = get_value_for_key(env, key);

	if (key[0] == '?')
	{
		key = ft_strjoin("$", key);
		arg = ft_str_remove(arg, key);
		arg = ft_str_insert(arg, ft_itoa(g_exit_code), i);
		return (arg);
	}

	// !	$$$$$??? -> ?
	if (should_add_dollar_sign(arg, i))
		key = ft_strjoin("$", key);
	arg = ft_str_remove(arg, key);

	if (arg && value)
	{
		arg = ft_str_insert(arg, value, i);
		printf("Arg after insert: %s\n", arg);
	}

	// free (key);
	// free (value);
	return (arg);
}

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

// !	echo "hello $USER$TERM more "
// !	echo "hello $USER more"
// !	echo hello$USER
// !	echo "hello $NOT_A_KEY"
// TODO protect str_remove() & str_insert() 
char	*will_expand(char **env, char *arg)
{
	int		i;
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
