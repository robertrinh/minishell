/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:54:04 by qbeukelm          #+#    #+#             */
/*   Updated: 2024/02/08 17:40:31 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int		execute_pipe(t_shell *shell, t_ast_node *ast_c)
{
	int		pipefd[2] = {10, 20};
	int		result = 0;
	pid_t	pid[2];

	result = pipe(pipefd);

	dup2(pipefd[0], 10);
	dup2(pipefd[1], 20);

	if (pid[0] == 0)
	{
		// Command	
	}
	else
	{
		pid[1] = fork();
	}

	// pid: 3132131
	// 0
	// 0
	
	// Pass to command
	// Is pid = 0?
	// Write(L) or Read(R)?
	
	// Wait for children before parent continues
	
	return (0);
}
