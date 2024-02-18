/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_command.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 14:28:14 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/02/16 17:07:32 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void print_2d_char(char **arr)
{
	int i = 0;
	while (arr[i])
	{
		printf("2D[%d] %s\n", i, arr[i]);
		i++;
	}
}

char	**format_cmd(t_ast_node *ast_c)
{
	int			i;
	char		**cmd_and_args;
	
	i = 0;
	cmd_and_args = malloc(sizeof(char *) * (ast_c->num_children + 2));  //TODO protect
	if (ast_c->type == COMMAND)
		cmd_and_args[0] = ast_c->value;
	while (i < ast_c->num_children)
	{
		cmd_and_args[i + 1] = ft_strdup(ast_c->children[i]->value); //TODO protect
		i++;
	}
	cmd_and_args[i + 1] = NULL;
	return (cmd_and_args);
}

static int	manage_execution(char *cmd_path, char **cmd_and_args, t_shell *shell)
{
	int		exit_code;
	pid_t	pid;
	
	exit_code = 0;
	pid = fork();
	if (pid == 0)
		exit_code = execve(cmd_path, cmd_and_args, shell->envp);
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		return (exit_code);
	}
	return (-1);
}

char	*get_path_for_cmd(char **env_paths, char *command)
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
	
	env_path = getenv("PATH");
	if (!env_path)
	{
		//TODO error message ->example cmd not found
	}
	env_paths = ft_split(env_path, ':');
	if (!env_paths)
	{
		//TODO protect
	}
	return (env_paths);
}

int		execute_command(t_shell *shell, t_ast_node *ast_c)
{
	char 	**env_paths;
	char	*cmd_path;
	int		exit_code = 0;
	char	**cmd_and_args;
	
	printf("\n\n--- cmd ---\n");
	printf("[%s]\n\n", ast_c->value);

	env_paths = get_paths();
	cmd_path = get_path_for_cmd(env_paths, ast_c->value);
	cmd_and_args = format_cmd(ast_c);

	if (in_pipeline(ast_c))
	{
		printf("in pipeline\n");
		manage_execution_pipe(cmd_path, ast_c, shell);
	}
	else
		exit_code = manage_execution(cmd_path, cmd_and_args, shell); // * No pipe, single command
	
	// TODO no pipes
	// exit_code = manage_execution(cmd_path, cmd_and_args, shell);

	return (0); // Return status code
}
