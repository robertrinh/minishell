/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:28:14 by qbeukelm          #+#    #+#             */
/*   Updated: 2024/02/02 15:28:35 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Get path

// Handle environment

// Make a process for command

#include "../../../includes/minishell.h"

bool	manage_execution(char *env_path, t_ast_node *ast, t_shell *shell)
{
	int	result;

	char *commands[] = {"echo", "Hello world", 0};
	
	result = execve(env_path, commands, shell->envp);
	printf("Result: %d\n", result);
}

int	get_cmd(char *env_path, char *commands)
{
	while (env_path)
	{
		if (access(commands, F_OK))
			return (commands);
	}
}

static char	**get_paths(char **envp)
{
	char	*env_path;
	char	*env_paths;
	
	env_path = getenv("PATH");
	if (!env_path)
	{
		//TODO error message ->example cmd not found
	}
	env_paths = ft_split(env_path, ":");
	if (!env_paths)
	{
		//TODO protect
	}
	return (env_paths);
}

bool	execute_command(t_shell *shell)
{
	char *env_path;

	
	printf("\n\n========execute========\n");
		
	env_path = get_paths(shell->envp);
	printf("PATH: %s\n", env_path);
	manage_execution(env_path, NULL, shell);
	

	return (SUCCESS);
}
