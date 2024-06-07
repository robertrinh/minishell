/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_environment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:45:47 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/06/07 14:25:46 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**format_cmd(t_cmd *cmd)
{
	int			i;
	char		**cmd_and_args;

	i = 0;
	cmd_and_args = safe_malloc(sizeof(char *) * (cmd->arg_count + 2));
	cmd_and_args[0] = safe_strdup(cmd->value);
	while (i < cmd->arg_count)
	{
		cmd_and_args[i + 1] = safe_strdup(cmd->args[i]);
		i++;
	}
	cmd_and_args[i + 1] = 0;
	return (cmd_and_args);
}

/*
	Returns the full path to the executable command. 
	Returns CMD_NOT_FOUND_STR "?" for command not found. And returns NULL 
	when there is no command.
*/
static char *get_path_error_string(void)
{
	char *str = malloc(2);
	str[0] = '?';
	str[1] = '\0';
	return (str);
}

char	*get_path_for_cmd(char **env_paths, char *command)
{
	char	*temp_path;
	char	*command_path;
	int		i;
	
	if (command == NULL)
		return (NULL);
	i = 0;
	while (env_paths[i])
	{
		temp_path = ft_strjoin(env_paths[i], "/");
		if (temp_path == NULL)
			return (NULL);
		command_path = ft_strjoin(temp_path, command);
		free(temp_path);
		if (command_path == NULL)
			return (NULL);
		if (access(command_path, F_OK) == 0)
			return (command_path);
		free(command_path);
		i++;
	}
	return (get_path_error_string());
}

/*
	Returns and array of strings for values contained in the environment PATH 
	variable following '=', and seperated by ':'. Or NULL if no PATH is found.
*/
char	**get_paths(t_shell *shell)
{
	char	*env_path;
	char	**env_paths;

	env_paths = NULL;
	env_path = NULL;
	env_path = get_value_for_key(shell->envp, "PATH");
	if (env_path == NULL)
		return (NULL);
	env_paths = ft_split(env_path, ':');
	if (env_paths == NULL)
		return (NULL);
	free(env_path);
	return (env_paths);
}
