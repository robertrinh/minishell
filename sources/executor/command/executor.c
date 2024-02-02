/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:16:50 by qbeukelm          #+#    #+#             */
/*   Updated: 2024/02/02 19:16:53 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

HANDLE_FUNCTIONS handle_functions[] = {
	execute_command
};

static void	execute_ast(t_shell *shell, t_ast_node *ast)
{
	int		i = 0;

	if (ast == NULL)
		return ;
	
	handle_functions[ast->type](shell, ast);

	while (i < ast->num_children)
	{
		if (ast->children)
            execute_ast(shell, ast->children[i]);
		i++;
	}

	if (ast->left)
		execute_ast(shell, ast->left);
	if (ast->right)
		execute_ast(shell, ast->right);
}

int		execute(t_shell *shell)
{
	execute_ast(shell, shell->ast);
	return (0);
}
