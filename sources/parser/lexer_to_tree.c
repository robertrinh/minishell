/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_to_tree.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/18 13:57:36 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/01/18 21:21:21 by quentinbeuk   ########   odam.nl         */
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

static t_token	*locate_pipe(t_token *current)
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
				ast->right->children = malloc(sizeof(t_ast_node)); //TODO malloc check
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
				ast->left->children = malloc(sizeof(t_ast_node)); // TODO Malloc for arg count
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

	printf("\n\n========tokens to tree========\n");
	
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
				ast->right = ast_constructor(current, NULL);
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
