/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 19:53:12 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/01/24 23:22:04 by quentinbeuk   ########   odam.nl         */
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
		else if (ast == ast->parent->right)
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
		traverse_ast(ast->left, depth - 2);
	if (ast->right)
		traverse_ast(ast->right, depth + 2);
}

int		parse_lexer(t_token *tokens_root)
{
	t_ast_node *ast_root;

	printf("\n\n========parser========\n");
	
	if (check_pipes(tokens_root) == FAILURE)
		return (exit_with_message(ERROR_UNMATCHED_PIPE, RED));

	if (locate_next_pipe(tokens_root) == NULL)
		ast_root = tokens_to_tree_simple(tokens_root, ast_root);
	else
		ast_root = tokens_to_ast(tokens_root, ast_root);
	traverse_ast(ast_root, 8);
	return (SUCCESS);
}

// TODO add to unit tests
// Happy case
// cmd1 arg1 | cmd2 arg2 arg2 | cmd3 arg3

// * Fixed
// what if | there are | pipes | that dont end 
// -> command with no children

// * Fixed
// what if | there are | pipes that |
// -> segfault when there is a pipe at the end = (PRE-FILTER)

// TODO
// cmg arg || cmd arg
// -> behaves as one pipe

// * Fixed
// cmd arg arg arg arg arg arg arg arg arg arg arg arg arg arg | cmd arg
// -> memory problem

// * Fixed
// cat "file1" "file2" "file3"
// -> a command without a pipe

// * Fixed
// cmd < input.txt
// cmd > output.txt

// TODO
// cmd >> output.txt | grep "a"
// >> output.txt (created txt with nothing in it)
// echo >> (give error)
// cat tasks.md > grep "a". "a" is arg of cat. grep is argfile. (out of scope)?
// same goes for >>

// ! Args after third redirect (Wrong parent)
// test this > out arg arg arg arg > out2 arg

// TODO in << heredoc
// Handle 'EOF' / "..."
// These are shorthand used in heredoc
// cat << END > output.txt
