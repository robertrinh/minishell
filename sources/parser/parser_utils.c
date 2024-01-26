/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 22:22:42 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/01/26 21:14:23 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parse *init_parse(t_token *tokens_root)
{
	t_parse		*p;

	p = malloc(sizeof(t_parse));
	if (p == NULL)
	{
		// TODO clean_exit()
		return (NULL);
	}
	p->ast_c = NULL;
	p->ast_r = NULL;
	p->tokens_c = tokens_root;
	p->tokens_r = tokens_root;
	return (p);
}

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
