/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 19:53:12 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/01/11 20:41:52 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
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

	switch (ast->type)
	{
		case COMMAND:
			printf("command: %s\n", ast->value);
			break ;
		case OPERATOR:
			printf("command: %s\n", ast->value);
			break ;
		case ARGUMENT:
			printf("argument: %s\n", ast-> value);
			break ;
		default:
			printf("unknown type\n");
			break ;		
	}

	while (i < ast->num_children)
	{
		traverse_ast(ast->children[i], depth + 1);
		i++;
	}
}

void parse(void) {
    printf("\n\n========parser========\n");

    t_ast_node node1 = {COMMAND, "ls", NULL, 0};
    t_ast_node node2 = {OPERATOR, "|", NULL, 0};
    t_ast_node node3 = {COMMAND, "grep", NULL, 0};
    t_ast_node node4 = {ARGUMENT, "file.txt", NULL, 0};

    t_ast_node child1 = {COMMAND, "echo", NULL, 0};
    t_ast_node child2 = {ARGUMENT, "hello", NULL, 0};

    t_ast_node root = {OPERATOR, "root", (t_ast_node*[]){&node1, &node2, &node3, &node4}, 4};
    node1.children = (t_ast_node*[]){&child1, &child2};
    node1.num_children = 2;

    traverse_ast(&root, 0);
}
