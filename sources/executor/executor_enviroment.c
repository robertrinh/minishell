/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_enviroment.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 19:45:47 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/02/22 20:25:09 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**format_cmd(t_cmd *cmd)
{
	int			i;
	char		**cmd_and_args;
	
	i = 0;
	cmd_and_args = malloc(sizeof(char *) * (cmd->arg_count + 2)); // TODO protect
	cmd_and_args[0] = cmd->value;
	while (i < cmd->arg_count)
	{
		cmd_and_args[i + 1] = ft_strdup(cmd->args[i]); // TODO protect
		i++;
	}
	cmd_and_args[i + 1] = 0;
	return (cmd_and_args);
}

char	*get_path_for_cmd(char **env_paths, char *command)
{
	char	*temp_path;
	char	*command_path;
	int		i;

	i = 0;
	while (env_paths[i])
	{
		temp_path = ft_strjoin(env_paths[i], "/");
		command_path = ft_strjoin(temp_path, command);
		if (access(command_path, 0) == 0)
			return (command_path);
		i++;
	}
	return (NULL);
}

char	**get_paths(void)
{
	char	*env_path;
	char	**env_paths;
	
	env_path = getenv("PATH");
	if (env_path == NULL)
	{
		//TODO clean_exit()
	}
	env_paths = ft_split(env_path, ':');
	if (env_paths == NULL)
	{
		//TODO clean_exit()
	}
	return (env_paths);
}
