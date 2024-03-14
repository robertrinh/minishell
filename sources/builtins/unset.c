/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 21:02:51 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/13 21:21:24 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		unset(t_cmd* cmd, t_shell *shell)
{
	index_for_env_key(shell, cmd->args[0]);
	return (0);
}
