/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_to_tree_new.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 20:36:31 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/01/25 01:06:43 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_parse
{
	t_ast_node	*ast_r;
	t_ast_node	*ast_c;
	t_token		*tokens_c;
	t_token		*tokens_r;
} t_parse;

typedef enum e_direction
{
	LEFT,
	RIGHT
} t_direction;

static t_parse *init_parse(t_token *tokens_root, t_ast_node *ast_root)
{
	t_parse		*p;

	p = malloc(sizeof(t_parse));
	if (p == NULL)
	{
		// TODO clean_exit()
		return (NULL);
	}
	p->ast_c = ast_root;
	p->ast_r = ast_root;
	p->tokens_c = tokens_root;
	p->tokens_r = tokens_root;
	return (p);
}

t_token	*fill_start_location(t_token *tokens_root, t_token *current, int pipe_count)
{
	if (pipe_count == 0)
		return (tokens_root);
	else if (locate_pipe_n(tokens_root, pipe_count))
		return (locate_pipe_n(tokens_root, pipe_count)->next);
	return (current);
}

bool	construct_pipe_node(t_parse *p, int pipe_count)
{
	p->tokens_c = locate_pipe_n(p->tokens_c, pipe_count);
	printf("constructed pipe->next: %s\n", p->tokens_c->next->value);
	if (p->ast_c->value)
	{
		p->ast_c->right = ast_constructor(p->tokens_c, p->ast_c);
		p->ast_c = p->ast_c->right;
	}
	else
	{
		p->ast_c = ast_constructor(p->tokens_c, NULL);
		p->ast_r = p->ast_c;
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

bool	construct_parent_node(t_parse *p, t_token *current, t_direction direction)
{
	if (direction == LEFT)
	{
		if (p->ast_c->left->children == NULL)
			p->ast_c->left->children = malloc(sizeof(t_ast_node) * count_children(current)); // TODO
	}
	if (direction == RIGHT)
	{
		if (p->ast_c->right->children == NULL)
			p->ast_c->right->children = malloc(sizeof(t_ast_node) * count_children(current)); // TODO
	}
	return (SUCCESS);
}

bool 	append_child_node(t_parse *p, t_token *current, int i, t_direction direction)
{
	printf("appending child: %s\n", current->value);
	if (direction == LEFT)
		p->ast_c->left->children[i] = ast_constructor(current, p->ast_c);
	if (direction == RIGHT)
		p->ast_c->right->children[i] = ast_constructor(current, p->ast_c);
	return (SUCCESS);
}

bool	assign_num_children(t_parse *p, int i, t_direction direction)
{
	printf("num children: %d\n", i + 1);
	if (direction == LEFT)
		p->ast_c->left->num_children = i + 1;
	if (direction == RIGHT)
		p->ast_c->right->num_children = i + 1;
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
			printf("constructing parent: %s\n", current->value);
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

// test this | and that | three more

bool	fill_ast_for_direction(t_parse *p, int pipe_count, t_direction direction)
{
	p->tokens_c = fill_start_location(p->tokens_r, p->tokens_c, pipe_count);
	printf("start location: %s \t pipe: %d\n", p->tokens_c->value, pipe_count);
	construct_command_node(p, direction);
	construct_arg_nodes(p, direction);

	return (SUCCESS);
}

t_ast_node	*tokens_to_ast(t_token *tokens_root, t_ast_node *ast_root)
{
	int				pipe_count;
	t_parse			*p;

	pipe_count = 0;
	p = init_parse(tokens_root, ast_root); // TODO free

	while (p->tokens_c)
	{
		// Assign pipes
		if (locate_pipe_n(p->tokens_r, pipe_count))
		{
			printf("located pipe: %s\tpipe: %d\n", p->tokens_c->value, pipe_count);
			construct_pipe_node(p, pipe_count);
			fill_ast_for_direction(p, pipe_count, LEFT);
			printf("current after fill left: %s\n\n", p->tokens_c->value);
			pipe_count++;
		}
		else
		{
			printf("No pipe, fill right: %s\n", p->tokens_c->value);
			if (p->tokens_c->next)
				p->tokens_c = p->tokens_c->next;
			fill_ast_for_direction(p, pipe_count, RIGHT);
		}
		p->tokens_c = p->tokens_c->next;
	}
	return (p->ast_r);
}
