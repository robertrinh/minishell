/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 21:25:42 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/13 23:12:26 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_delimiters(char *arg_value, char delimiter)
{
	int 	i;
	int		delimiter_count;

	i = 0;
	delimiter_count = 0;
	while (arg_value[i])
	{
		if (arg_value[i] == delimiter)
			delimiter_count++;
		i++;
	}
	return (delimiter_count);
}

static bool is_valid_export_arg(char *arg)
{
	int		delimiter_count;

	if (arg == NULL)
		return (false);

	delimiter_count = count_delimiters(arg, '=');

	if (delimiter_count == 1)
		return (true);

	return (false);
}

static char	*env_key_from_arg(char *arg)
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

static size_t env_realloc_size(char **env, char *str)
{
    size_t		current_size;
	size_t		new_size;
    char		**temp;

	current_size = 0;
	new_size = 0;
	temp = env;
    while (*temp != NULL) {
        current_size += strlen(*temp) + 1;
        temp++;
    }
    new_size = current_size + (ft_strlen(str) + 1);
    return (new_size);
}

static void	add_arg_to_env(t_shell *shell, char *arg)
{
	int		incert_index;
	char	*save_line;
	char	*key;

	key = env_key_from_arg(arg);
	incert_index = index_for_env_key(shell, key);
	free (key);
    shell->envp = ft_realloc(shell->envp, env_realloc_size(shell->envp, arg));
	if (incert_index == -1)
	{
		incert_index = index_for_env_key(shell, "_");
		save_line = shell->envp[incert_index];
		shell->envp[incert_index] = malloc(strlen(arg) + 1);
   		shell->envp[incert_index] = arg;
		shell->envp[incert_index + 1] = malloc(strlen(save_line) + 1);
		shell->envp[incert_index + 1] = save_line;
		shell->envp[incert_index + 2] = NULL;
	}
	else
	{
		shell->envp[incert_index] = malloc(strlen(arg) + 1);
		shell->envp[incert_index] = arg;
	}
}

// !	export A=1 B=2 C=3 D=4 E=5 F=6 G=7 H=8 I=9 J=10
int		export(t_cmd* cmd, t_shell *shell)
{
	int		i;

	i = 0;
	while (i < cmd->arg_count)
	{
		if (is_valid_export_arg(cmd->args[i]))
			add_arg_to_env(shell, cmd->args[i]);
		i++;
	}

	return (0);
}
