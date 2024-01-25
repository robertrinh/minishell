/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_to_tree.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/18 13:57:36 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/01/25 01:09:22 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_node	*ast_constructor(t_token *current, t_ast_node *parent)
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

bool	contains_pipe(t_token *current)
{
	if (current->type == PIPE)
		return (true);
	return (false);
}

t_token	*locate_pipe_n(t_token *tokens_root, int pipe_count)
{
	int			i;
	t_token 	*current;
	
	i = 0;
	current = tokens_root;
	if (pipe_count == 0)
		return (current);
	while (current)
	{
		if (current->type == PIPE)
		{
			if (i == pipe_count)
			{
				printf("pipe[%d]: %s\n", i, current->next->value);
				return (current);
			}
			i++;
		}
		if (current->next == NULL)
			return (NULL);
		
		current = current->next;
	}
	return (NULL);
}

t_token	*locate_next_pipe(t_token *tokens)
{
	t_token *current;

	current = tokens;
	while (current)
	{
		if (current->type == PIPE)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int count_children(t_token *current_cmd)
{
	int			count;
	t_token		*current;

	count = 0;
	current = current_cmd;
	while (current)
	{
		if (current->type == ARGUMENT)
			count++;
		if (current->type == PIPE)
			return (count);
		current = current->next;
	}
	return (count);
}


static t_token	*fill_right(t_token *tokens_root, t_ast_node *ast, int pipe_count)
{
	t_token	*current;
	int	i;

	i = 0;
	// current = fill_start_location(tokens_root, pipe_count);
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


static t_token	*fill_left(t_token *tokens_root, t_ast_node *ast, int pipe_count)
{
	t_token	*current;
	int	i;

	i = 0;
	// current = fill_start_location(tokens_root, pipe_count);
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
		if (locate_next_pipe(current))
		{
			current = locate_next_pipe(current);
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
