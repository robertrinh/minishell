/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_manager.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/29 13:17:01 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/03/28 17:30:12 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_validation	dup_fds(t_pipes *pipes, t_cmd *cmd)
{
	t_validation	validation;

	validation = SUCCESS;

	if (pipes->prev_pipe[READ] != -1)
	{
        close(pipes->prev_pipe[WRITE]);
        dup2(pipes->prev_pipe[READ], STDIN_FILENO);
        close(pipes->prev_pipe[READ]);
    }
	if (pipes->curr_pipe[WRITE] != -1)
	{
		close(pipes->curr_pipe[READ]);
		if (cmd->fd_out)
			validation = redirect_out(cmd);
		else
			dup2(pipes->curr_pipe[WRITE], STDOUT_FILENO);
		close(pipes->curr_pipe[WRITE]);
	}

	return (validation);
}
