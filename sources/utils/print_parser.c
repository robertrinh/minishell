/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_parser.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 21:05:40 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/02/01 21:08:18 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_depth(int	depth)
{
	int	i = 0;
	while (i < depth)
	{
		printf("    ");
		i++;
	}
}

void	print_ast(t_ast_node *ast, int depth)
{
	int		i = 0;

	if (ast == NULL)
		return ;

	print_depth(depth);
	
	if (ast->parent != NULL)
	{
		if (ast == ast->parent->left)
			printf("/L-- ");
		else if (ast->type == ARGUMENT)
			printf("-- ");
		else if (ast == ast->parent->right)
			printf("\\R-- ");
	}
	
	handle_functions_print[ast->type](ast);

	while (i < ast->num_children)
	{
		if (ast->children)
            print_ast(ast->children[i], depth + 1);
		i++;
	}

	if (ast->left)
		print_ast(ast->left, depth - 2);
	if (ast->right)
		print_ast(ast->right, depth + 2);
}
