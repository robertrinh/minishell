/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_parser_operations.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 21:05:37 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/02/01 21:10:40 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_command(t_ast_node *ast)
{
	printf("command: %s\n", ast->value);
}

void	print_argument(t_ast_node *ast)
{
	printf("argument: %s\n", ast->value);
}

void	print_pipe(t_ast_node *ast)
{
	printf("pipe: %s\n", ast->value);
}

void	print_redirect(t_ast_node *ast)
{
	printf("redirect: %s\n", ast->value);
}

void	print_heredoc(t_ast_node *ast)
{
	printf("heredoc: %s\n", ast->value);
}

void	print_argfile(t_ast_node *ast)
{
	printf("argfile: %s\n", ast->value);
}

void	print_quote(t_ast_node *ast)
{
	printf("quote: %s\n", ast->value);
}

void	print_unknown(t_ast_node *ast)
{
	printf("unknown type\n");
}

HANDLE_FUNCTIONS_PRINT handle_functions_print[] = {
	print_command,
	print_argument,
	print_pipe,
	print_redirect,
	print_heredoc,
	print_quote,
	print_argfile,
	print_unknown,
};
