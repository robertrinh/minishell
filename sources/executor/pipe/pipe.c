/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/08 15:54:04 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/02/11 12:55:49 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

int		execute_pipe(t_shell *shell, t_ast_node *ast_c)
{
	int		result = 0;

	ast_c->pids = init_pids();
	result = pipe(ast_c->pids->pipefd);

	printf("pidfd[0]: %d\n", ast_c->pids->pipefd[0]);
	printf("pidfd[0]: %d\n", ast_c->pids->pipefd[1]);
	// ast_c->pids->pipefd[0] = fork();
	
	return (0);
}