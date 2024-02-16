/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/08 15:54:04 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/02/16 16:52:53 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	execute_pipe(t_shell *shell, t_ast_node *ast_c)
{
	shell->current_pipe += 1;

	printf("\n\n--- pipe[%d] ---\n", shell->current_pipe);
	printf("pidfd[0]: %d\n", ast_c->pids->pipefd[0]);
	printf("pidfd[1]: %d\n", ast_c->pids->pipefd[1]);

	return (1);
}
