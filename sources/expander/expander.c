/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/16 11:15:41 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/07/25 17:30:17 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
 
static bool	expand_arg(char *arg, t_shell *shell, t_vec *vec, size_t *i)
{
	char	*key;
	char	*value;

	if (ft_strlen(arg) == 1)
		return (ft_vec_push(vec, arg[*i]), SUCCESS);
	key = get_env_key(arg, *i, shell);
	if (key == NULL)
		return (FAILURE);
	if (key[0] == '?')
		return (expand_exit_code(vec, shell), (*i)++, SUCCESS);
	value = get_value_for_key(shell->envp, key, shell);
	if (value == NULL)
	{
		(*i) += ft_strlen(key);
		return (free(key), SUCCESS); 
	}
	(*i) += ft_strlen(key);
	free(key);
	if (!ft_vec_push_str(vec, value))
		return (show_error_message(E_MALLOC, shell, "", X_FAILURE), FAILURE);
	free (value);
	return (SUCCESS);
}

bool	will_expand(char *arg, t_shell *shell, t_vec *vec)
{
	size_t	i;
	int		expand_count;

	expand_count = count_expand(arg);
	if (expand_count == 0)
		return (SUCCESS); // ? needed after should_not_expand implementation?
	i = 0;
	while (arg[i])
	{
		if (arg[i] == EXPAND_CHAR)
		{
			skip_multiple_expand_chars(arg, &i);
			if (expand_arg(arg, shell, vec, &i) == false)
				return (FAILURE);
		}
		else if (!is_quote(arg[i])) // ! < new_strip_quotes + this intervenes with each other
			if (!ft_vec_push(vec, arg[i]))
				return (show_error_message(E_MALLOC, shell, "", X_FAILURE), FAILURE);
		i++;
	}
	return (SUCCESS);
}

// * notes:

// ? echo hello"more more"hello = Incorrect output -> spacebar hello. Bash: hellomore more hello
// ? echo "hello '$USER' more" = Incorrect output: Ours stripped single quotes (with no strip quotes enabled)
// ? echo "hello $USER"$TERM" more" = Incorrect output: Ours does not print more at the end
// ? echo "hello $USER'$TERM' more" = Incorrect output: Ours does not print single quotes

// * commenting out new_strip_quotes in post_parser_process makes echo "hello" not functioning

// * having new_strip_quotes active makes vector print output twice:
// * [minishell]: echo "hello $TERM$NOARG more"
// * hello xterm-256color morehello $TERM$NOARG more

// ! remaining issues regarding quote stripping.
