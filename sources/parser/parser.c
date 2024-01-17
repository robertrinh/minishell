/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 19:53:12 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/01/17 17:24:19 by quentinbeuk   ########   odam.nl         */
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


static void	print_depth(int	depth)
{
	int	i = 0;
	while (i < depth)
	{
		printf("\t");
		i++;
	}
}

static void	traverse_ast(t_ast_node *ast, int depth)
{
	int		i = 0;

	if (ast == NULL)
		return ;

	print_depth(depth);
	handle_functions[ast->type](ast);

	while (i < ast->num_children)
	{
		traverse_ast(ast->children[i], depth + 1);
		i++;
	}
}

void parse(void) {
    printf("\n\n========parser========\n");

	// cat "file_1.txt" "file_2.txt" | grep "a" | wc
    t_ast_node node1 = {COMMAND, "cat", NULL, 0};
    t_ast_node node2 = {ARGUMENT, "file_1.txt", NULL, 0};
	t_ast_node node3 = {ARGUMENT, "file_2.txt", NULL, 0};
    t_ast_node node4 = {PIPE, "|", NULL, 0};
    t_ast_node node5 = {COMMAND, "grep", NULL, 0};
    t_ast_node node6 = {ARGUMENT, "a", NULL, 0};
    t_ast_node node7 = {PIPE, "|", NULL, 0};
    t_ast_node node8 = {COMMAND, "wc", NULL, 0};

	t_ast_node *pipe_children_1[] = {&node1, &node5};
	node4.children = pipe_children_1;
	node4.num_children = 2;

	t_ast_node *pipe_children_2[] = {&node4, &node8};
	node7.children = pipe_children_2;
	node7.num_children = 2;

    t_ast_node* cat_children[] = {&node2, &node3};
    node1.children = cat_children;
    node1.num_children = 2;

    t_ast_node* grep_children[] = {&node6};
    node4.children = grep_children;
    node4.num_children = 1;

    traverse_ast(&node7, 0);
}
