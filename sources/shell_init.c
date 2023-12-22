/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:04:02 by qtrinh            #+#    #+#             */
/*   Updated: 2023/12/22 14:37:08 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static t_cmd *cmd_init(void)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
	{
		// TODO exit
	}
	cmd->single_quote = 0;
	cmd->double_quote = 0;
	return (cmd);
}

t_shell	*shell_init()
{
	t_shell *shell;

	shell = malloc(sizeof(t_shell));
	if (shell == NULL)
	{
		// TODO exit
	}
	shell->cmd = cmd_init();
	return (shell);
}
