/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 19:53:12 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/02/01 21:07:55 by quentinbeuk   ########   odam.nl         */
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

int		parse_lexer(t_token *tokens_root)
{
	t_ast_node *ast_root;

	printf("\n\n========parser========\n");
	if (check_pipes(tokens_root) == FAILURE)
		return (exit_with_message(ERROR_UNMATCHED_PIPE, RED));
	
	if (locate_pipe_n(tokens_root, 0))
		ast_root = tokens_to_parser_pipe(tokens_root);
	else
		ast_root = tokens_to_parser(tokens_root);
	
	print_ast(ast_root, 8);
	return (SUCCESS);
}
