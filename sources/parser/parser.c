/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 19:53:12 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/01/18 21:37:35 by quentinbeuk   ########   odam.nl         */
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
		printf("    ");
		i++;
	}
}

static void	traverse_ast(t_ast_node *ast, int depth)
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
		else
			printf("\\R-- ");
	}

	handle_functions[ast->type](ast);

	while (i < ast->num_children)
	{
		if (ast->children)
            traverse_ast(ast->children[i], depth + 1);
		i++;
	}
	
	if (ast->left)
		traverse_ast(ast->left, depth + 1);
	if (ast->right)
		traverse_ast(ast->right, depth + 1);
}

int		parse_lexer(t_token *tokens_root)
{
	t_ast_node *ast_root;

	if (check_pipes(tokens_root) == FAILURE)
		return (exit_with_message(ERROR_UNMATCHED_PIPE, RED));
	
	ast_root = tokens_to_tree(tokens_root, ast_root);
	traverse_ast(ast_root, 0);

	return (SUCCESS);
}

// Happy case
// cmd1 arg1 | cmd2 | cmd3 arg3

// ! Fixed
// what if | there are | pipes | that dont end 
// -> command with no children

// ! Fixed
// what if | there are | pipes that |
// -> segfault when there is a pipe at the end = (PRE-FILTER)

// ! Fixed
// cmg arg || cmd arg
// -> double pipe = (PRE-FILTER)

// TODO
// cmd arg arg arg arg arg arg arg | cmd arg
// -> memory problem
