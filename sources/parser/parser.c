/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 19:53:12 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/01/15 19:13:21 by quentinbeuk   ########   odam.nl         */
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

	// cat "file.txt" | grep "a" | wc
    t_ast_node node1 = {COMMAND, "cat", NULL, 0};
    t_ast_node node2 = {ARGUMENT, "file.txt", NULL, 0};
    t_ast_node node3 = {OPERATOR, "|", NULL, 0};
    t_ast_node node4 = {COMMAND, "grep", NULL, 0};
    t_ast_node node5 = {ARGUMENT, "a", NULL, 0};
    t_ast_node node6 = {OPERATOR, "|", NULL, 0};
    t_ast_node node7 = {COMMAND, "wc", NULL, 0};

    t_ast_node* catChildren[] = {&node2};
    node1.children = catChildren;
    node1.num_children = 1;

    t_ast_node* grepChildren[] = {&node5};
    node4.children = grepChildren;
    node4.num_children = 1;

    t_ast_node* rootChildren[] = {&node1, &node3, &node4, &node6, &node7};
    t_ast_node root = {OPERATOR, "root", rootChildren, 5};

    traverse_ast(&root, 0);
}
