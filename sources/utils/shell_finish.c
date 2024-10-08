/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_finish.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:15:55 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/09/02 13:30:43 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	lexer_finish(t_shell *shell)
{
	shell->single_quote = 0;
	shell->double_quote = 0;
}

static void	free_cmd_table(t_cmd_table *cmd_table)
{
	int	i;

	i = 0;
	if (!cmd_table)
		return ;
	while (i < cmd_table->cmd_count)
	{
		free_cmd(cmd_table->cmds[i]);
		cmd_table->cmds[i] = NULL;
		i++;
	}
	free(cmd_table->cmds);
	cmd_table->cmd_count = 0;
	cmd_table->cmds = NULL;
}

static void	free_shell_struct(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->cmd_table)
	{
		free(shell->cmd_table);
		shell->cmd_table = NULL;
	}
	if (shell->envp)
	{
		free_2d_array(shell->envp);
		shell->envp = NULL;
	}
	exit_with_message(E_EOF_DESCRIPTOR, shell, EXIT_SUCCESS);
	free(shell);
}

void	free_shell(t_shell *shell, bool close_shell)
{
	if (shell->split)
	{
		free_split(shell->split);
		shell->split = NULL;
	}
	if (shell->tokens)
	{
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
	if (shell->cmd_table->cmds)
		free_cmd_table(shell->cmd_table);
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (close_shell == true)
		free_shell_struct(shell);
}

void	shell_finish(t_shell *shell)
{
	lexer_finish(shell);
	free_shell(shell, false);
	if (dup2(shell->original_stdin, STDIN_FILENO) < 0)
	{
		show_error(E_DUP, shell, "", X_FAILURE);
		return ;
	}
	should_print("\n--------------------End--------------------\n\n", \
		shell->print_output);
}
