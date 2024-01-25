/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_to_tree_simple.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 20:08:12 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/01/24 20:35:49 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
				parent->children = malloc(sizeof(t_ast_node)); // check size
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