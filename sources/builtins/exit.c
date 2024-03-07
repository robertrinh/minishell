/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:41:20 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/03/07 14:56:05 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		exit_shell(t_cmd* cmd, t_shell *shell)
{
	ft_putstr_fd("exit minishell\n", STDOUT_FILENO);
	exit(g_exit_status);
	return (0);
}
