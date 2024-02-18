/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_to_parser_pipe.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/26 14:07:58 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/02/16 14:23:01 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	fill_ast_for_direction(t_parse *p, int pipe_count, t_direction dir)
{
	p->tokens_c = fill_start_location(p->tokens_r, p->tokens_c, pipe_count);
	construct_command_node(p, dir);
	construct_arg_nodes(p, dir);
	construct_redirect_nodes(p, pipe_count);
	return (SUCCESS);
}

t_ast_node	*tokens_to_parser_pipe(t_token *tokens_root)
{
	int				pipe_count;
	t_parse			*p;

	pipe_count = 0;
	p = init_parse(tokens_root); // TODO free
	while (p->tokens_c)
	{
		if (locate_pipe_n(p->tokens_r, pipe_count))
		{
			construct_pipe_node(p, pipe_count);
			fill_ast_for_direction(p, pipe_count, LEFT);
			pipe_count++;
		}
		else
		{
			if (p->tokens_c->next && pipe_count > 0)
				p->tokens_c = p->tokens_c->next;
			fill_ast_for_direction(p, pipe_count, RIGHT);
			break ;
		}
		p->tokens_c = p->tokens_c->next;
	}
	return (p->ast_r);
}
