/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_to_parser.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 22:31:32 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/01/25 22:40:47 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	fill_ast_for_direction(t_parse *p, int pipe_count, t_direction direction)
{
	p->tokens_c = fill_start_location(p->tokens_r, p->tokens_c, pipe_count);
	printf("start: %s\n", p->tokens_c->value);
	construct_command_node(p, direction);
	construct_arg_nodes(p, direction);

	construct_redirect_nodes(p, pipe_count);
	printf("Done \n\n");

	return (SUCCESS);
}

t_ast_node	*tokens_to_parser(t_token *tokens_root, t_ast_node *ast_root)
{
	int				pipe_count;
	t_parse			*p;

	pipe_count = 0;
	p = init_parse(tokens_root, ast_root); // TODO free

	while (p->tokens_c)
	{
		printf("start of loop[%d]: %s\n", pipe_count, p->tokens_c->value);
		printf("next pipe n: %p\n", locate_pipe_n(p->tokens_r, pipe_count));
		if (locate_pipe_n(p->tokens_r, pipe_count))
		{
			construct_pipe_node(p, pipe_count);
			fill_ast_for_direction(p, pipe_count, LEFT);
			pipe_count++;
		}
		else
		{
			printf("making right\n");
			if (p->tokens_c->next && pipe_count > 0)
				p->tokens_c = p->tokens_c->next;
			fill_ast_for_direction(p, pipe_count, RIGHT);
			printf("BREAK\n");
			break ;
		}
		p->tokens_c = p->tokens_c->next;
	}
	printf("DONE: %p\n", p->ast_r);
	return (p->ast_r);
}
