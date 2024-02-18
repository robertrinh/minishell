/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_to_parser.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/26 14:08:07 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/02/16 14:21:02 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	append_child_node(t_parse *p, int i)
{
	p->ast_c->children[i] = ast_constructor(p->tokens_c, p->ast_c);
	return (SUCCESS);
}

static bool	make_command_and_children(t_parse *p)
{
	int	i;

	i = 0;
	while (p->tokens_c)
	{
		if (p->ast_c == NULL)
			make_command_node(p);
		if (p->tokens_c->type == ARGUMENT)
		{
			make_parent_node(p);
			append_child_node(p, i);
			i++;
		} 
		if (p->tokens_c->next == NULL)
			p->ast_c->num_children = i;
		p->tokens_c = p->tokens_c->next;
	}
	return (SUCCESS);
}

static bool	make_argfile_node(t_parse *p)
{
	p->ast_c->children = malloc(sizeof(t_ast_node));
	p->ast_c->children[0] = ast_constructor(p->tokens_c, p->ast_c);
	p->ast_c->num_children = 1;
	return (SUCCESS);
}

static bool	make_redirects(t_parse *p)
{
	while (p->tokens_c)
	{
		if (p->tokens_c->type == REDIRECT || p->tokens_c->type == HEREDOC)
		{
			make_redirect_node(p);
		}
		if (p->tokens_c->type == ARGFILE)
			make_argfile_node(p);
		if (p->ast_c->left)
			p->ast_c = p->ast_c->left;
		p->tokens_c = p->tokens_c->next;
	}
	return (SUCCESS);
}

bool	make_command_node(t_parse *p)
{
	if (p->tokens_c->type == COMMAND)
	{
		p->ast_c = ast_constructor(p->tokens_c, NULL);
		p->ast_r = p->ast_c;
	}
	return (SUCCESS);
}

bool	make_parent_node(t_parse *p)
{
	if (p->ast_c->children == NULL)
		p->ast_c->children = malloc(sizeof(t_ast_node) * count_children(p->tokens_c)); // TODO protect
	return (SUCCESS);
}

bool	make_redirect_node(t_parse *p)
{
	p->ast_c->left = ast_constructor(p->tokens_c, p->ast_c);
	return (SUCCESS);
}

t_ast_node	*tokens_to_parser(t_token *tokens_root)
{
	t_parse	*p;

	p = init_parse(tokens_root); // TODO free
	make_command_and_children(p);
	p->tokens_c = p->tokens_r;
	make_redirects(p);
	return (p->ast_r);
}
