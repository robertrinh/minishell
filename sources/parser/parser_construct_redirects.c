/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_construct_redirects.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:54:45 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/02/15 15:13:07 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int count_pipes_for_parse(t_parse *p)
{
	t_token		*current;
	int			count;

	current = p->tokens_r;
	count = 0;
	while (current)
	{
		if (current->type == PIPE)
			count++;
		current = current->next;
	}
	return (count);
}

static bool	construct_redirect_node(t_parse *p, t_token *current)
{
	if (p->ast_c->left)
		p->ast_c = p->ast_c->left;
	p->ast_c->left = ast_constructor(current, p->ast_c);
	return (SUCCESS);
}

bool construct_argfile_node(t_parse *p, t_token *current)
{
	if (current->type == ARGFILE)
	{
		p->ast_c->left->children = malloc(sizeof(t_ast_node)); // TODO protect
		p->ast_c->left->children[0] = ast_constructor(current, p->ast_c->left);
		p->ast_c->left->num_children = 1;
	}
	return (SUCCESS);
}

bool	construct_redirect_nodes(t_parse *p, int pipe_count)
{
	t_ast_node	*ast_place_holder;
	t_token		*current;
	int			total_pipes;

	total_pipes = count_pipes_for_parse(p);
	ast_place_holder = p->ast_c;
	current = p->tokens_c;
	while (current)
	{
		if (current->type == REDIRECT || current->type == HEREDOC)
		{
			if (total_pipes == pipe_count && p->ast_c->right)
				p->ast_c = p->ast_c->right;
			construct_redirect_node(p, current);
			current = current->next;
			construct_argfile_node(p, current);
		}
		if (current->type == PIPE || current->next == NULL)
		{
			p->ast_c = ast_place_holder;
			return (SUCCESS);
		}
		current = current->next;
	}
	return (SUCCESS);
}
