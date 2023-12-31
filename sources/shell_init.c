/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:04:02 by qtrinh            #+#    #+#             */
/*   Updated: 2024/01/06 12:51:25 by qbeukelm         ###   ########.fr       */
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

void	input_init(char *input, t_shell *shell)
{
	shell->input = ft_calloc(sizeof(char), ft_strlen(input) + 1);
	if (shell->input == NULL)
	{	
		// TODO exit
	}
	shell->input = input;
}

t_split	*init_split(t_shell *shell, t_split *split)
{
	split->input = malloc(sizeof(char) * ft_strlen(shell->input) + 1);
	if (split->input == NULL)
	{
		// TODO clean_exit()
	}
	split->input = shell->input;
	split->len = ft_strlen(shell->input);
	split->i = 0;
	split->i_check = 0;
	split->count = 0;
	split->i_buff = 0;
	split->i_str = 0;
	split->strings = 0;
	return (split);
}
