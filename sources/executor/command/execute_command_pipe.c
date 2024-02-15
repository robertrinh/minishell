/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 11:59:06 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/02/15 16:58:41 by qbeukelm         ###   ########.fr       */
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

static bool direct_pipes(t_shell *shell, t_ast_node *ast_c)
{
	// First pipe
	if (shell->current_pipe == 1)
	{
		close(ast_c->parent->pids->pipefd[0]);
		dup2(ast_c->parent->pids->pipefd[0], STDIN_FILENO);
		printf("dup %d -> %d\n", ast_c->parent->pids->pipefd[0], STDIN_FILENO);
		printf("close %d\n", ast_c->parent->pids->pipefd[0]);
		
		// First and last pipe
		if (shell->current_pipe == shell->total_pipes)
		{
			printf("dup %d -> %d\n", ast_c->parent->pids->pipefd[1], STDOUT_FILENO);
			dup2(ast_c->parent->pids->pipefd[1], STDOUT_FILENO);
			close(ast_c->parent->pids->pipefd[1]);
		}

		// First pipe && Multiple pipes
		if (shell->total_pipes > 1)
		{
			printf("dup %d -> %d\n", ast_c->parent->pids->pipefd[1], ast_c->parent->right->pids->pipefd[0]);
			dup2(ast_c->parent->pids->pipefd[1], ast_c->parent->right->pids->pipefd[0]);
			close(ast_c->parent->pids->pipefd[1]);
			printf("close %d\n", ast_c->parent->pids->pipefd[1]);
		}
	}
	
	// Not first pipe && last
	else if (shell->current_pipe == shell->total_pipes)
	{
		printf("not first pipe && last pipe\n");
		printf("dup %d -> %d\n", ast_c->parent->pids->pipefd[1], STDOUT_FILENO);
		dup2(ast_c->parent->pids->pipefd[1], STDOUT_FILENO);
		close(ast_c->parent->parent->pids->pipefd[1]);
		printf("close %d\n", ast_c->parent->parent->pids->pipefd[1]);
	}
	return (SUCCESS);
}

// ! cat README.md | grep a | wc
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
		direct_pipes(shell, ast_c);
		exit_code = execve(cmd_path, cmd_and_args, shell->envp);
	}
	else if (ast_c->parent->pids->pid[0] > 0)
	{
		// ! PARENT
		close(ast_c->parent->pids->pipefd[1]);
		printf("waiting for PID %d\n", ast_c->parent->pids->pid[0]);
		waitpid(ast_c->parent->pids->pid[0], NULL, 0);
	}
	return (exit_code);
}

static int perform_right(char *cmd_path, t_ast_node *ast_c, t_shell *shell)
{
	int		exit_code = 0;
	char	**cmd_and_args;

	cmd_and_args = format_cmd(ast_c);

	printf("goes into right\n");
	ast_c->parent->pids->pid[1] = fork();
	if (ast_c->parent->pids->pid[1] == -1)
	{
		// TODO handle_error()
	}
	if (ast_c->parent->pids->pid[1] == 0)
	{
		close(ast_c->parent->pids->pipefd[1]);
		printf("close %d\n", ast_c->parent->pids->pipefd[1]);
		
		printf("dup %d -> %d\n", ast_c->parent->pids->pipefd[0], STDIN_FILENO);
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
	printf("direction is %d\n", direction);

	shell->total_pipes = count_pipes(shell); // TODO move

	if (direction == LEFT)
		exit_code = perform_left(cmd_path, ast_c, shell);
	else if (direction == RIGHT)
	{
		// printf("RIGHT\n");
		// exit_code = perform_right(cmd_path, ast_c, shell);
	}
	return (exit_code);
}
