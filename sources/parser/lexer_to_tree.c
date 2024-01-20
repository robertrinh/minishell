/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_to_tree.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/18 13:57:36 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/01/20 11:53:26 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	contains_pipe(t_token *current)
{
	if (current->type == PIPE)
		return (true);
	return (false);
}

static t_token	*locate_pipe_n(t_token *current, int count)
{
	int	i;

	i = 0;
	while (current)
	{
		if (current->type == PIPE)
		{
			if (i == count - 1)
				return (current->next);
			i++;
		}
		current = current->next;
	}
	return (NULL);
}

t_token	*locate_pipe(t_token *current)
{
	while (current)
	{
		if (current->type == PIPE)
			return (current);
		current = current->next;
	}
	return (NULL);
}


static t_ast_node	*ast_constructor(t_token *current, t_ast_node *parent)
{
	t_ast_node *ast;

	ast = malloc(sizeof(t_ast_node));
	if (ast == NULL)
	{
		// TODO clean_exit()
	}
	ast->type = current->type;
	ast->value = current->value;
	ast->children = NULL;
	ast->num_children = 0;
	ast->parent = parent;
	ast->left = NULL;
	ast->right = NULL;
	return (ast);
}


static int count_children(t_token *current_cmd)
{
	int			count;
	t_token		*current;

	count = 0;
	current = current_cmd;

	if (current->type != ARGUMENT)
		return (0);
	
	while (current)
	{
		if (current->type == ARGUMENT)
			count++;
		if (current->type != ARGUMENT)
			return (count);
		current = current->next;
	}
	return (count);
}


static t_token	*fill_right(t_token *tokens_root, t_ast_node *ast, int count)
{
	t_token	*current;
	int	i;

	i = 0;
	if (count == 0)
		current = tokens_root;
	else
		current = locate_pipe_n(tokens_root, count);
	while (current)
	{
		if (current->type == COMMAND)
			ast->right = ast_constructor(current, ast);
		if (current->type == ARGUMENT)
		{
			if (ast->right->children == NULL)
				ast->right->children = malloc(sizeof(t_ast_node) * count_children(current)); // TODO protect
			ast->right->children[i] = ast_constructor(current, ast);
			ast->right->num_children = i + 1;
			i++;
		}
		current = current->next;
	}
	return (current);
}


static t_token	*fill_left(t_token *tokens_root, t_ast_node *ast, int count)
{
	t_token	*current;
	int	i;

	i = 0;
	if (count == 0)
		current = tokens_root;
	else
		current = locate_pipe_n(tokens_root, count);
	while (current)
	{
		if (current->type == COMMAND)
			ast->left = ast_constructor(current, ast);
		else if (current->type == ARGUMENT)
		{
			if (ast->left->children == NULL)
				ast->left->children = malloc(sizeof(t_ast_node) * count_children(current)); // TODO protect
			ast->left->children[i] = ast_constructor(current, ast);
			i++;
		}
		if (contains_pipe(current))
		{
			ast->left->num_children = i + 1;
			return (current);
		}
		current = current->next;
	}
	return (current);
}


t_ast_node	*tokens_to_tree(t_token *tokens_root, t_ast_node *ast_root)
{
	t_token		*current;
	t_ast_node	*ast;
	int 		pipe_count;
	
	ast = NULL;
	current = tokens_root;
	pipe_count = 0;
	while (current)
	{
		if (locate_pipe(current))
		{
			current = locate_pipe(current);
			if (ast)
			{
				ast->right = ast_constructor(current, ast);
				ast = ast->right;
			}
			else
			{
				ast = ast_constructor(current, NULL);
				ast_root = ast;
			}
			current = fill_left(tokens_root, ast, pipe_count);
			pipe_count++;
		}
		else
			current = fill_right(tokens_root, ast, pipe_count);
		if (current)
			current = current->next;
	}
	return (ast_root);
}

static t_token		*append_children(t_token *tokens, t_ast_node *ast, t_ast_node *parent)
{
	int		i;
	t_token	*current;

	i = 0;
	current = tokens;
	if (current->type == COMMAND && current->next != NULL)
		current = current->next;

	while (current)
	{
		if (ast->children == NULL)
			ast->children = malloc(sizeof(t_ast_node) * count_children(current)); // TODO protect
		if (current->type != ARGUMENT)
		{
			ast->num_children = i + 1;
			return (current);
		}
		ast->children[i] = ast_constructor(current, ast);
		ast->num_children = i + 1;
		i++;
		if (current->next)
			current = current->next;
		else
			return (current);
	}
	ast->num_children = i + 1;
	return (current);
}

static t_token	*append_children_parent(t_token *tokens, t_ast_node *parent)
{
	t_token *current;
	int	i;

	i = 0;
	current = tokens;
	while (current)
	{
		if (current->type == ARGUMENT)
		{
			if (parent->num_children == 0)
				parent->children = malloc(sizeof(t_ast_node)); //check size
			parent->children[(parent->num_children - 1) + i] = ast_constructor(current, parent);
			parent->num_children = parent->num_children + i;
			i++;
		}
		if (is_special_type(current->type))
			return (current);
		if (current)
			current = current->next;
	}
	return (current);
}

t_ast_node  *tokens_to_tree_simple(t_token *tokens_root, t_ast_node *ast_root)
{
	t_token		*current;
	t_ast_node	*ast;

	current = tokens_root;
	ast = NULL;
	
	while (current)
	{
		if (current->type == COMMAND && ast == NULL)
		{
			ast = ast_constructor(current, NULL);
			ast_root = ast;
			current = append_children(current, ast, ast);
		}
		if (current->type == REDIRECT)
		{
			if (ast == NULL)
			{
				ast = ast_constructor(current, NULL);
				ast_root = ast;
			}
			if (ast)
			{
				ast->left = ast_constructor(current, ast);
				ast = ast->left;
				if (current->next)
				{
					current = current->next;
					if (current->type == ARGFILE)
					{
						ast->children = malloc(sizeof(t_ast_node));
						ast->children[0] = ast_constructor(current, ast);
						ast->num_children = 1;
					}
				}
				if (current->next)
				{
					current = current->next;
					current = append_children_parent(current, ast->parent);
					continue ;
				}
			}
		}
		if (current)
			current = current->next;
	}
	return (ast_root);
}

// redirects regarding pipes @ ast