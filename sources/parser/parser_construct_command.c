/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_construct_command.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 22:35:21 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/01/31 17:41:31 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	construct_parent_node(t_parse *p, t_token *current, t_direction direction)
{
	if (direction == LEFT)
	{
		if (p->ast_c->left->children == NULL)
			p->ast_c->left->children = malloc(sizeof(t_ast_node) * count_children(current)); // TODO protect
	}
	if (direction == RIGHT)
	{
		if (p->ast_c->right->children == NULL)
			p->ast_c->right->children = malloc(sizeof(t_ast_node) * count_children(current)); // TODO protect
	}
	return (SUCCESS);
}

static bool 	append_child_node(t_parse *p, t_token *current, int i, t_direction direction)
{
	if (direction == LEFT)
		p->ast_c->left->children[i] = ast_constructor(current, p->ast_c->left);
	if (direction == RIGHT)
		p->ast_c->right->children[i] = ast_constructor(current, p->ast_c->right);
	return (SUCCESS);
}

static bool	assign_num_children(t_parse *p, int i, t_direction direction)
{
	if (direction == LEFT)
		p->ast_c->left->num_children = i;
	if (direction == RIGHT)
		p->ast_c->right->num_children = i;
	return (SUCCESS);
}

bool	construct_arg_nodes(t_parse *p, t_direction direction)
{
	int		i;
	t_token	*current;

	i = 0;
	current = p->tokens_c;
	while (current)
	{
		if (current->type == ARGUMENT)
		{
			construct_parent_node(p, current, direction);
			append_child_node(p, current, i, direction);
			i++;
		}
		if (contains_pipe(current) || current->next == NULL)
		{
			assign_num_children(p, i, direction);
			return (SUCCESS);
		}
		current = current->next;
	}
	return (SUCCESS);
}

bool	construct_command_node(t_parse *p, t_direction direction)
{
	if (p->tokens_c->type == COMMAND)
	{
		if (direction == LEFT)
			p->ast_c->left = ast_constructor(p->tokens_c, p->ast_c);
		if (direction == RIGHT)
			p->ast_c->right = ast_constructor(p->tokens_c, p->ast_c);
	}
	if (p->tokens_c->next)
		p->tokens_c = p->tokens_c->next;
	return (SUCCESS);
}
