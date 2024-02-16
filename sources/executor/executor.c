/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 19:16:50 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/02/16 14:17:44 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute_ast(t_shell *shell, t_ast_node *ast)
{
	int	i;

	i = 0;
	if (ast == NULL)
		return ;

	// TODO skip arguments
	shell->exec_funcs[ast->type](shell, ast);

	while (i < ast->num_children)
	{
		if (ast->children)
            execute_ast(shell, ast->children[i]);
		i++;
	}
	if (ast->left)
		execute_ast(shell, ast->left);
	if (ast->right)
		execute_ast(shell, ast->right);
}

static t_pids	*init_pids(void)
{
	t_pids	*pids;

	pids = malloc(sizeof(t_pids));
	if (pids == NULL)
	{
		// TODO clean_exit()
	}
	pids->pipefd[0] = 0;
	pids->pipefd[1] = 0;
	pids->pid[0] = (pid_t) -1;
    pids->pid[1] = (pid_t) -1;
	return (pids);
}

static void open_pipe(t_ast_node *ast_c)
{
	int	result;
	
	ast_c->pids = init_pids();
	result = pipe(ast_c->pids->pipefd);
	if (result < 0)
	{
		// TODO clean_exit
	}
}

static void open_pipes(t_ast_node *ast)
{
	if (ast == NULL)
		return ;

	if (ast->type == PIPE)
		open_pipe(ast);
	if (ast->left)
		open_pipes(ast->left);
	if (ast->right)
		open_pipes(ast->right);
}

int		execute(t_shell *shell)
{

	printf("\n\n========execute========\n");
	open_pipes(shell->ast);
	execute_ast(shell, shell->ast);

	return (0);
}
