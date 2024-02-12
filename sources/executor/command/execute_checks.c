/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_checks.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/11 11:21:49 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/02/11 12:58:19 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	in_pipeline(t_ast_node *ast_c)
{
	if (ast_c->parent)
	{
		if (ast_c->parent->type == PIPE && ast_c->parent->pids)
			return (true);
	}
	return (false);
}
