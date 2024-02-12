/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_command_pipe.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/11 11:59:06 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/02/11 16:07:33 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_direction node_direction(t_ast_node *ast_c)
{
	if (ast_c->parent)
	{
		if (ast_c->parent->type == PIPE)
		{
			if (ast_c->parent->left == ast_c)
				return LEFT;
			if (ast_c->parent->right == ast_c)
				return RIGHT;
		}
	}
	return (-1);
}

static int	perform_left(char *cmd_path, t_ast_node *ast_c, t_shell *shell)
{
	int		exit_code = 0;
	char	**cmd_and_args;

	cmd_and_args = format_cmd(ast_c);

	ast_c->parent->pids->pid[0] = fork();
	if (ast_c->parent->pids->pid[0] == -1)
	{
		// TODO handle_error()
	}
	if (ast_c->parent->pids->pid[0] == 0)
	{
		close(ast_c->parent->pids->pipefd[0]);
		dup2(ast_c->parent->pids->pipefd[1], STDOUT_FILENO);
		close(ast_c->parent->pids->pipefd[1]);

		exit_code = execve(cmd_path, cmd_and_args, shell->envp);
	}
	else if (ast_c->parent->pids->pid[0] > 0)
	{
		close(ast_c->parent->pids->pipefd[1]);
		waitpid(ast_c->parent->pids->pid[0], NULL, 0);
	}
	return (exit_code);
}

static int perform_right(char *cmd_path, t_ast_node *ast_c, t_shell *shell)
{
	int		exit_code = 0;
	char	**cmd_and_args;

	cmd_and_args = format_cmd(ast_c);

	ast_c->parent->pids->pid[1] = fork();
	if (ast_c->parent->pids->pid[1] == -1)
	{
		// TODO handle_error()
	}
	if (ast_c->parent->pids->pid[1] == 0)
	{
		close(ast_c->parent->pids->pipefd[1]);
		dup2(ast_c->parent->pids->pipefd[0], STDIN_FILENO);
		close(ast_c->parent->pids->pipefd[0]);

		exit_code = execve(cmd_path, cmd_and_args, shell->envp);
	}
	else if (ast_c->parent->pids->pid[1] > 0)
	{
		close(ast_c->parent->pids->pipefd[0]);
		waitpid(ast_c->parent->pids->pid[1], NULL, 0);
	}
	return (exit_code);
}

int	manage_execution_pipe(char *cmd_path, t_ast_node *ast_c, t_shell *shell)
{
	int				exit_code = 0;
	t_direction 	direction;

	direction = node_direction(ast_c);

	if (direction == LEFT)
		exit_code = perform_left(cmd_path, ast_c, shell);
	else if (direction == RIGHT)
		exit_code = perform_right(cmd_path, ast_c, shell);
	return (exit_code);
}
