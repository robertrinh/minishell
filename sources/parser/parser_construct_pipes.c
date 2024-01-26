/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_construct_pipes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 22:34:33 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/01/26 13:35:27 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*fill_start_location(t_token *tokens_root, t_token *current, int pipe_count)
{
	if (pipe_count == 0)
		return (tokens_root);
	else if (locate_pipe_n(tokens_root, pipe_count - 1))
		return (locate_pipe_n(tokens_root, pipe_count - 1)->next);
	return (current);
}

bool	construct_pipe_node(t_parse *p, int pipe_count)
{
	p->tokens_c = locate_pipe_n(p->tokens_r, pipe_count);
	if (p->tokens_c->type == PIPE)
	{
		if (p->ast_c->value)
		{
			printf("ast != NULL: constructing pipe: %s\n", p->tokens_c->value);
			p->ast_c->right = ast_constructor(p->tokens_c, p->ast_c);
			p->ast_c = p->ast_c->right;
		}
		else
		{
			printf("ast = NULL: constructing pipe: %s\n", p->tokens_c->value);
			p->ast_c = ast_constructor(p->tokens_c, NULL);
			p->ast_r = p->ast_c;
		}
	}
	return (SUCCESS);
}
