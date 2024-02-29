/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:54:04 by qbeukelm          #+#    #+#             */
/*   Updated: 2024/02/29 14:00:24 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_pipes	*init_pipes(void)
{
	t_pipes	*pipes;

	pipes = safe_malloc(sizeof(t_pipes));
	pipes->prev_pipe[0] = -1;
	pipes->prev_pipe[1] = -1;
	pipes->curr_pipe[0] = -1;
	pipes->curr_pipe[1] = -1;
	return (pipes);
}

int count_pipes(t_shell *shell)
{
	t_token		*current;
	int			count;
	
	current = shell->tokens;
	count = 0;
	while (current)
	{
		if (current->type == PIPE)
			count++;
		current = current->next;
	}
	return (count);
}

void	will_open_pipe(t_cmd_table *cmd_table, t_pipes *pipes, int i)
{
    if (i < cmd_table->cmd_count - 1)
        pipe(pipes->curr_pipe);
}

void	will_close_pipes(t_pipes *pipes)
{
    if (pipes->prev_pipe[READ] != -1)
	{
        close(pipes->prev_pipe[READ]);
        close(pipes->prev_pipe[WRITE]);
	}
}

void	iterate_pipes(t_pipes *pipes)
{
    pipes->prev_pipe[READ] = pipes->curr_pipe[READ];
    pipes->prev_pipe[WRITE] = pipes->curr_pipe[WRITE];
}
