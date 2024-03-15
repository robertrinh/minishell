/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 21:02:51 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/14 17:49:15 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char **buffer_env_after_index(char **env, int index)
{
	int		i;
	int		buffer_len;
	char	**buffer;

	i = 0;
	buffer_len = count_lines_from(env, index) + 1;
	buffer = (char **)safe_malloc(sizeof(char *) * buffer_len);
	while (env[index])
	{
		buffer[i] = safe_malloc(sizeof(char *) * ft_strlen(env[index]));
		buffer[i] = env[index];
		i++;
		index++;
	}
	return (buffer);
}

static void	incert_env_buffer(char **env, char **buffer, int env_index)
{
	int		buffer_index;

	buffer_index = 0;
	while (env[env_index])
	{
		env[env_index] = buffer[buffer_index];
		buffer_index++;
		env_index++;
	}
	env[env_index + 1] = NULL;
}

static void	remove_line_from_env(char **env, char *key)
{
	int		remove_index;
	char	**buffer;

	remove_index = index_for_env_key(env, key);
	if (remove_index >= 0)
	{
		buffer = buffer_env_after_index(env, (remove_index + 1));
		incert_env_buffer(env, buffer, remove_index);
	}
}

// TODO add to test set ->	unset HOME PATH SHELL USER PWD TERM ZSH
int		unset(t_cmd* cmd, t_shell *shell)
{
	int		i;
	int		new_size;

	i = 0;
	while (i < cmd->arg_count)
	{
		remove_line_from_env(shell->envp, cmd->args[i]);
		i++;
	}
	new_size = env_size(shell->envp);
	ft_realloc(shell->envp, new_size);
	return (0);
}
