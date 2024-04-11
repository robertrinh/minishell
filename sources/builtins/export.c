/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 21:25:42 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/04/10 14:29:33 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
# define UNSERSCORE_VAR "_"

/*
	Counts the occurances of the given delimiter character in the given string
*/
static int	count_delimiters(const char *arg, char delimiter)
{
	int 	i;
	int		delimiter_count;

	i = 0;
	delimiter_count = 0;
	while (arg[i])
	{
		if (arg[i] == delimiter)
			delimiter_count++;
		i++;
	}
	return (delimiter_count);
}

static bool	is_valid_export_key(const char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == EXPORT_DELIMITER)
			break ;
		if (ft_isalpha(arg[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

static bool is_valid_export_arg(const char *arg)
{
	if (arg == NULL)
		return (false);

	if (count_delimiters(arg, EXPORT_DELIMITER) > 1)
		return (false);

	if (is_valid_export_key(arg) == false)
		return (false);

	return (true);
}

static char	*env_key_from_arg(const char *arg)
{
	int		i;
	char	*key;

	i = 0;
	key = malloc(sizeof(char *) * ft_strlen(arg));
	while (arg[i])
	{
		if (arg[i] == '=')
			return (key);
		key[i] = arg[i];
		i++;
	}
	return (NULL);
}

/*
	Returns the size of env 
*/
static size_t env_realloc_size(char **env, char *str)
{
    size_t		current_size;
	size_t		new_size;

	current_size = env_size(env);
    new_size = current_size + (sizeof(char *) * ft_strlen(str) + 1);
    return (new_size);
}

static void	add_arg_to_env(t_shell *shell, char *arg)
{
	int		insert_index;
	char	*save_line;
	char	*key;

	key = env_key_from_arg(arg);
	insert_index = index_for_env_key(shell->envp, key);
	free (key);
    shell->envp = ft_realloc(shell->envp, env_realloc_size(shell->envp, arg));
	if (insert_index == -1)
	{
		insert_index = index_for_env_key(shell->envp, UNSERSCORE_VAR);
		if (insert_index == -1)
			insert_index = (count_lines_from(shell->envp, 0) - 1);
		save_line = shell->envp[insert_index];
		shell->envp[insert_index] = safe_malloc(ft_strlen(arg) + 1);
   		shell->envp[insert_index] = arg;
		shell->envp[insert_index + 1] = safe_malloc(ft_strlen(save_line) + 1);
		shell->envp[insert_index + 1] = save_line;
		shell->envp[insert_index + 2] = NULL;
	}
	else
	{
		shell->envp[insert_index] = safe_malloc(ft_strlen(arg) + 1);
		shell->envp[insert_index] = arg;
	}
}

int		export(t_cmd *cmd, t_shell *shell)
{
	int		i;

	i = 0;
	if (cmd->args[i] == NULL)
		return (show_error_message(E_EXPORT, C_RED, "", X_EXPORT));
	while (i < cmd->arg_count)
	{
		if (is_valid_export_arg(cmd->args[i]))
			add_arg_to_env(shell, cmd->args[i]);
		else
			show_error_message(E_EXPORT, C_RED, cmd->args[i], X_EXPORT);
		i++;
	}
	return (0);
}
