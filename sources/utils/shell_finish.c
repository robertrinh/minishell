/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_finish.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/23 16:15:55 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/05/25 20:52:26 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	lexer_finish(t_shell *shell)
{
	shell->single_quote = 0;
	shell->double_quote = 0;
}

static void free_cmd_table(t_cmd_table *cmd_table)
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
	cmd_table->cmds = NULL;
}

static void	free_shell_struct(t_shell *shell)
{
	printf("only after exit \n"); // TODO delete later
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
	if (shell->builtin_main)
	{
		free(shell->builtin_main);
		shell->builtin_main = NULL;
	}
	if (shell->builtin_child)
	{
		free(shell->builtin_child);
		shell->builtin_child = NULL;
	}
	free(shell);
}

void	free_shell(t_shell *shell, bool close_shell)
{
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

// free (cmd_path);
void	shell_finish(t_shell *shell)
{
	lexer_finish(shell);
	free_shell(shell, false);
	if (dup2(shell->original_stdin, STDIN_FILENO) < 0)
	{
		show_error_message(E_DUP, C_RED, "", X_FAILURE);
		return ;
	}
	should_print("\n--------------------End--------------------\n\n", shell->print_output);
}