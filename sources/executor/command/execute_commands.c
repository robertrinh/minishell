/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_commands.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 15:22:01 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/02/22 17:53:02 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*get_path_for_cmd(char **env_paths, char *command)
{
	char	*temp_path;
	char	*command_path;
	int	i;

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

static char	**get_paths(void)
{
	char	*env_path;
	char	**env_paths;
	
	env_path = getenv("PATH"); //? make own getenv to traverse our copied env?
	if (!env_path)
	{
		//TODO error message -> cmd not found
	}
	env_paths = ft_split(env_path, ':');
	if (env_paths)
	{
		//TODO protect
	}
	return (env_paths);
}

int	execute_command(t_shell *shell)
{
	int	exit_code;
	char	**env_paths;
	char	**cmd_args;
	char	*cmd_path;
	int	i;

	i = 0; //* need to give actual position of cmd[i], better to pass it on as parameter
	env_paths = get_paths();
	cmd_path = get_path_for_cmd(env_paths, shell->cmd_table->cmds[i]->value);
	cmd_args = shell->cmd_table->cmds[i]->args;
	exit_code = 0;
	
	if (execve(cmd_path, cmd_args, shell->envp) == -1) //*execve excepts args + cmd, not just args -> changed in parser
	{
		//TODO error with exit code
	}
	return (0); // status code
}
