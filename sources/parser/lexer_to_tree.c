/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_to_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:57:36 by qbeukelm          #+#    #+#             */
/*   Updated: 2024/01/18 17:20:40 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// 0. traverse tokens

// 1. Identify PIPE

// 2. Identify COMMAND

// 3. Set ARGUMENTs as children

// 4. Set REDIRECTs as left/right

static bool	contains_pipe(t_token *current)
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
		//TODO clean_exit
	}
	ast->type = current->type;
	ast->value = current->value;
	ast->children = NULL; //list of children
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
	{
		current = locate_pipe_n(tokens_root, count);
		printf("current count: %s %d\n", current->value, current->i);
	}
	while (current)
	{
		if (current->type == COMMAND)
		{
			ast->right = ast_constructor(current, ast);
		}
		if (current->type == ARGUMENT)
		{
			if (ast->right->children == NULL)
				ast->right->children = malloc(sizeof(t_ast_node)); //TODO malloc check
			printf("Making child right; %s\n", current->value);
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
	{
		current = locate_pipe_n(tokens_root, count);
		printf("current count: %s %d\n", current->value, current->i);
	}
	while (current)
	{
		if (current->type == COMMAND)
		{
			ast->left = ast_constructor(current, ast);
			printf("ast left value: %s\n", ast->left->value);
		}
		if (current->type == ARGUMENT)
		{
			if (ast->left->children == NULL)
				ast->left->children = malloc(sizeof(t_ast_node)); // TODO Malloc for arg count
			ast->left->children[i] = ast_constructor(current, ast);
			printf("ast left value: %s\n", ast->left->children[i]->value);
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
// cat "" hi | grep "a" | wc -w
void	tokens_to_tree(t_token *tokens_root)
{
	printf("\n\n========tokens to tree========\n");

	t_token		*current;
	t_ast_node	*ast;
	t_ast_node	*ast_root;
	int 		pipe_count;
	
	ast_root = NULL;
	ast = NULL;
	current = tokens_root;
	pipe_count = 0;
	while (current)
	{
		if (locate_pipe(current))
		{
			current = locate_pipe(current);
			printf("current is: %s , pc: %d\n", current->value, pipe_count);
			printf("pointer ast is %p\n", ast);
			if (ast != NULL)
			{
				ast->right = ast_constructor(current, NULL);
				printf("ast right value: %s\n", ast->right->value);
				ast = ast->right;
			}
			else
			{
				ast = ast_constructor(current, NULL);
				ast_root = ast;
				printf("ast value: %s\n", ast->value);
			}
			current = fill_left(tokens_root, ast, pipe_count);
			printf("current fill left: %s\n", current->value);
			pipe_count++;
		}
		else
			current = fill_right(tokens_root, ast, pipe_count);
		if (current)
			current = current->next;
	}
	printf("\n\n");
	traverse_ast(ast_root, 0);
}

// ? what if | there are | pipes | that dont end 
// -> command with no children (no pipes) segfaults

// what if | there are | pipes that |
// -> segfault when there is a pipe at the end = (PRE-FILTER)

// cmd arg arg arg arg arg arg arg | cmd arg
// -> at 7 args??

// cmg arg || cmd arg
// -> double pipe = (PRE-FILTER)