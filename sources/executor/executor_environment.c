/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_environment.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 19:45:47 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/04/14 14:20:06 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**format_cmd(t_cmd *cmd)
{
	int			i;
	char		**cmd_and_args;

	i = 0;
	cmd_and_args = safe_malloc(sizeof(char *) * (cmd->arg_count + 2));
	cmd_and_args[0] = cmd->value;
	while (i < cmd->arg_count)
	{
		cmd_and_args[i + 1] = ft_strdup(cmd->args[i]); // TODO protect
		i++;
	}
	cmd_and_args[i + 1] = 0;
	return (cmd_and_args);
}

/*
	Returns the full path to the exicutable command. And NULL command is
	not found.
*/
char	*get_path_for_cmd(char **env_paths, char *command)
{
	char	*temp_path;
	char	*command_path;
	int		i;

	i = 0;
	while (env_paths[i])
	{
		temp_path = ft_strjoin(env_paths[i], "/"); // TODO protect + error
		command_path = ft_strjoin(temp_path, command); // TODO protect + error
		if (access(command_path, F_OK) == 0)
			return (command_path);
		i++;
	}
	return (NULL);
}

/*
	Returns the string value of the environment PATH variable following '='.
	Or NULL if no PATH is found.
*/
char	*ft_getenv(t_shell *shell, char *input)
{
	char	**local_env;
	int	i;

	local_env = shell->envp;
	i = 0;

	while (local_env[i])
	{
		if (ft_strncmp(local_env[i], input, ft_strlen(input + 1)) == 0)
			return (ft_substr(local_env[i], 5, ft_strlen(local_env[i])));
		i++;
	}
	return (NULL);
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
	env_path = ft_getenv(shell, "PATH");
	if (env_path == NULL)
		return (NULL);
	env_paths = ft_split(env_path, ':');
	if (env_paths == NULL)
		return (NULL);
	return (env_paths);
}
