/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:53:12 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/01/18 17:04:40 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
				 1 1     2 2
cat << EOF > file | wc -c | tr -d " " > file2


                          __ PIPELINE__
                     ___/              \____
                    /                       \
            COMMAND                    __ PIPELINE _
          /        \                  /             \
    ARGUMENTS   REDIRECTIONS      COMMAND         _ COMMAND __
        |          |     |           |           /            \
       cat        <<     >       ARGUMENTS    ARGUMENTS   REDIRECTIONS
                   |     |         |   |      |   |   |        |
                 "..."  file      wc  -c      tr  -d " "       >
                                                               |
                                                             file2

 */


t_ast_node *node_constructor(char *value, t_token_type type, t_ast_node *parent)
{
	t_ast_node *ast = malloc(sizeof(t_ast_node));
	ast->type = type;
	ast->value = value;
	ast->children = NULL;
	ast->num_children = 0;
	ast->parent = parent;
	ast->left = NULL;
	ast->right = NULL;
	return (ast);
}

static void	print_depth(int	depth)
{
	int	i = 0;
	while (i < depth)
	{
		printf("    ");
		i++;
	}
}

void	traverse_ast(t_ast_node *ast, int depth)
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

	handle_functions[ast->type](ast);

	if (ast->left)
		traverse_ast(ast->left, depth + 1);
	if (ast->right)
		traverse_ast(ast->right, depth + 1);

	while (i < ast->num_children)
	{
		traverse_ast(ast->children[i], depth + 1);
		i++;
	}
}

void parse(void)
{
    printf("\n\n========parser========\n");

	// cat "" "" | grep "a" | wc -w

	// root
	t_ast_node *ast = node_constructor("|", PIPE, NULL);
	
	// cat
	ast->left = node_constructor("cat", COMMAND, ast);
	t_ast_node *cat_arg_1 = node_constructor("file_1.txt", ARGUMENT, ast->left);
	t_ast_node *cat_arg_2 = node_constructor("file_2.txt", ARGUMENT, ast->left);
	t_ast_node *cat_children[] = {cat_arg_1, cat_arg_2};
	ast->left->children = cat_children;
	ast->left->num_children = 2;

	// pipe
	ast->right = node_constructor("|", PIPE, ast);

	// grep
	t_ast_node *grep = node_constructor("grep", COMMAND, ast->right);
	t_ast_node *grep_args = node_constructor("a", ARGUMENT, ast->right);
	t_ast_node *grep_children[] = {grep_args};
	grep->children = grep_children;
	grep->num_children = 1;
	ast->right->left = grep;
	
	// wc
	t_ast_node *wc = node_constructor("wc", COMMAND, ast->right);
	t_ast_node *wc_args = node_constructor("-w", ARGUMENT, ast->right);
	t_ast_node *wc_children[] = {wc_args};
	wc->children = wc_children;
	wc->num_children = 1;
	ast->right->right = wc;

	traverse_ast(ast, 0);
}
