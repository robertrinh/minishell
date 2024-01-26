/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_operations.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 22:42:15 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/01/25 22:42:21 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_command(t_ast_node *ast)
{
	printf("command: %s\n", ast->value);
}

void	handle_argument(t_ast_node *ast)
{
	printf("argument: %s\n", ast->value);
}

void	handle_pipe(t_ast_node *ast)
{
	printf("pipe: %s\n", ast->value);
}

void	handle_redirect(t_ast_node *ast)
{
	printf("redirect: %s\n", ast->value);
}

void	handle_heredoc(t_ast_node *ast)
{
	printf("heredoc: %s\n", ast->value);
}

void	handle_argfile(t_ast_node *ast)
{
	printf("argfile: %s\n", ast->value);
}

void	handle_quote(t_ast_node *ast)
{
	printf("quote: %s\n", ast->value);
}

void	handle_unknown(t_ast_node *ast)
{
	printf("unknown type\n");
}

HANDLE_FUNCTIONS handle_functions[] = {
	handle_command,
	handle_argument,
	handle_pipe,
	handle_redirect,
	handle_heredoc,
	handle_quote,
	handle_argfile,
	handle_unknown,
};
