/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_commands.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 15:22:01 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/02/22 22:21:22 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	prepare_command(t_shell *shell, int i)
{
	char	**env_paths;
	char	*cmd_path;

	env_paths = get_paths();
	shell->cmd_table->cmds[i]->formatted_cmd = format_cmd(shell->cmd_table->cmds[i]);
	cmd_path = get_path_for_cmd(env_paths, shell->cmd_table->cmds[i]->value);
	shell->cmd_table->cmds[i]->cmd_path = cmd_path;
	
	return (SUCCESS);
}

int	execute_command(t_shell *shell, int i)
{
	char	*cmd_path;
	char	**formatted_cmd;

	cmd_path = shell->cmd_table->cmds[i]->cmd_path;
	formatted_cmd = shell->cmd_table->cmds[i]->formatted_cmd;

	execve(cmd_path, formatted_cmd, shell->envp);

	return (SUCCESS);
}

// HELPERS ^

// cat tasks.md | wc
// cat tasks.md | wc -w | wc

static int new_process(t_shell *shell, int i, int *prev_pipe, int *c_pipe) {
    pid_t pid;

    pid = fork();
    if (pid == 0) 
	{
        // Child process
        if (prev_pipe[READ] != -1)
		{
            close(prev_pipe[WRITE]);
            dup2(prev_pipe[READ], STDIN_FILENO);
            close(prev_pipe[READ]);
        }

        if (c_pipe[WRITE] != -1)
		{
            close(c_pipe[READ]);
            dup2(c_pipe[WRITE], STDOUT_FILENO);
            close(c_pipe[WRITE]);
        }

        execute_command(shell, i);
    }
	else if (pid > 0)
	{
		// Close the previous pipe ends if not the first command
        if (prev_pipe[READ] != -1)
		{
            close(prev_pipe[READ]);
            close(prev_pipe[WRITE]);
        }

        waitpid(pid, NULL, 0);
    }
    return SUCCESS;
}

int execute_commands(t_shell *shell) {
    int i;
    int prev_pipe[2] = {-1, -1};
    int c_pipe[2];

	i = 0;
    while (i < shell->cmd_table->cmd_count) 
	{
        printf("cmd[%d]\n", i);
        prepare_command(shell, i);

        // Only create a pipe if not the last command
        if (i < shell->cmd_table->cmd_count - 1)
            pipe(c_pipe);

        new_process(shell, i, prev_pipe, c_pipe);

        // Update prev_pipe for the next iteration
        prev_pipe[READ] = c_pipe[READ];
        prev_pipe[WRITE] = c_pipe[WRITE];

		i++;
    }

    // Close the last pipe ends
    if (prev_pipe[READ] != -1)
	{
        close(prev_pipe[READ]);
        close(prev_pipe[WRITE]);
    }

    return SUCCESS;
}
