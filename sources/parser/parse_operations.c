/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_operations.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 15:54:28 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/01/17 17:19:47 by quentinbeuk   ########   odam.nl         */
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
	handle_unknown,
};
