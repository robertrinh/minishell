/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 21:25:42 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/05/31 17:06:34 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*env_key_from_arg(const char *arg)
{
	int		i;
	char	*key;

	i = 0;
	key = safe_malloc(sizeof(char *) * ft_strlen(arg));
	while (arg[i])
	{
		if (arg[i] == '=')
		{
			key[i] = '\0';
			return (key);
		}
		key[i] = arg[i];
		i++;
	}
	return (NULL);
}

static void	add_new_arg(t_shell *shell, char *arg)
{
	int		count;
	int		i;
	char	**new_env;

	i = 0;
	count = count_lines_from(shell->envp, 0);
	new_env = ft_realloc(shell->envp, (count + 2) * sizeof(char *));
	if (new_env == NULL)
	{
		show_error_message(E_MALLOC, C_RED, "", X_FAILURE);
		return ;
	}
	while (shell->envp[i])
	{
		new_env[i] = safe_strdup(shell->envp[i]);
		free(shell->envp[i]);
		i++;
	}
	free(shell->envp);
	new_env[count] = safe_strdup(arg);
	new_env[count + 1] = NULL;
	shell->envp = new_env;
}

static void	add_arg_to_env(t_shell *shell, char *arg)
{
	int		insert_index;
	char	*key;

	key = env_key_from_arg(arg);
	insert_index = index_for_env_key(shell->envp, key);
	if (insert_index != -1)
	{
		free(shell->envp[insert_index]);
		shell->envp[insert_index] = safe_strdup(arg);
	}
	else
		add_new_arg(shell, arg);
	free(key);
}

int	export(t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 0;
	if (cmd->args[i] == NULL)
		return (show_error_message(E_EXPORT, C_RED, "", X_FAILURE));
	while (i < cmd->arg_count)
	{
		if (is_valid_export_arg(cmd->args[i]))
			add_arg_to_env(shell, cmd->args[i]);
		else
			return (show_error_message(E_EXPORT, C_RED, cmd->args[i], 1));
		i++;
	}
	return (0);
}
