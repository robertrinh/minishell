/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/03 09:41:20 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/06 18:07:43 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		exit_shell(t_cmd *cmd)
{
	ft_putstr_fd("exit minishell\n", STDOUT_FILENO);
	exit(g_exit_status);
	return (0);
}
