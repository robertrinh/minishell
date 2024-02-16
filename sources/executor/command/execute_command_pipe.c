/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_command_pipe.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/11 11:59:06 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/02/16 17:27:05 by qtrinh        ########   odam.nl         */
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
		printf("dup2 %d <- %d\n", ast_c->parent->pids->pipefd[WRITE], STDOUT_FILENO);
		printf("close %d\n", ast_c->parent->pids->pipefd[WRITE]);
		close(ast_c->parent->pids->pipefd[READ]);
		dup2(ast_c->parent->pids->pipefd[WRITE], STDOUT_FILENO);
		close(ast_c->parent->pids->pipefd[WRITE]);
		
		//! if current pipe = total pipe wont work in this as if statement the pipe is always 1, therefore deleted
		//First pipe && Multiple pipes //? not sure if this is needed.
		// if (shell->total_pipes > 1)
		// {
		// 	printf("dup %d -> %d\n", ast_c->parent->pids->pipefd[READ], ast_c->parent->right->pids->pipefd[WRITE]);
		// 	printf("multiple pipes trigger \n");
		// 	dup2(ast_c->parent->pids->pipefd[READ], ast_c->parent->right->pids->pipefd[WRITE]);
		// 	close(ast_c->parent->pids->pipefd[WRITE]);
		// 	close(ast_c->parent->pids->pipefd[READ]);
		// 	printf("close %d\n", ast_c->parent->pids->pipefd[READ]);
		// }
	}
	
	// Not first pipe && last
	else if (shell->current_pipe == shell->total_pipes)
	{
		printf("not first pipe && last pipe\n"); //! is printing
		printf("dup2 %d <- %d\n", ast_c->parent->pids->pipefd[READ], ast_c->pids->pipefd[WRITE]); //? not printing
		printf("close %d\n", ast_c->parent->pids->pipefd[READ]);  //? not printing
		dup2(ast_c->parent->parent->pids->pipefd[WRITE], ast_c->parent->pids->pipefd[WRITE]); //? dup2 is not registering, can't figure out why.
		close(ast_c->left->pids->pipefd[READ]); //? dup2 parameters are incorrect anyway, so you can ignore the correctness of it (was testing)
		// * this is the linking pipe, if dup2 works here correctly i figure it would work entirely!
	}
	return (SUCCESS);
}

// ! cat README.md | grep minishell | wc
// ! echo hello | grep h | wc
// ! cat README.md | wc

static int	perform_left(char *cmd_path, t_ast_node *ast_c, t_shell *shell)
{
	int		exit_code;
	char	**cmd_and_args;

	exit_code = 0;
	cmd_and_args = format_cmd(ast_c);
	ast_c->parent->pids->pid[0] = fork();
	// printf("goes left\n");
	if (ast_c->parent->pids->pid[0] == -1)
	{
		// TODO handle_error() + closing pipes
	}
	if (ast_c->parent->pids->pid[0] == 0)
	{
		// ! CHILD
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
		// TODO handle_error() + closing pipes
	}
	if (ast_c->parent->pids->pid[1] == 0)
	{
		close(ast_c->parent->pids->pipefd[WRITE]);
		printf("dup %d -> %d\n", ast_c->parent->pids->pipefd[READ], STDIN_FILENO);
		printf("close %d\n", ast_c->parent->pids->pipefd[READ]);
		dup2(ast_c->parent->pids->pipefd[READ], STDIN_FILENO); //? have to check linking pipe regarding dup2.
		close(ast_c->parent->pids->pipefd[READ]);
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
	shell->total_pipes = count_pipes(shell); // TODO move

	if (direction == LEFT)
		exit_code = perform_left(cmd_path, ast_c, shell);
	else if (direction == RIGHT)
		exit_code = perform_right(cmd_path, ast_c, shell);
	return (exit_code);
}
