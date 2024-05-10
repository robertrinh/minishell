/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_exit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/07 12:29:05 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/05/10 18:13:23 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	free_tokens(t_token *tokens_head)
// {
// 	t_token	*current;
// 	t_token	*next;

// 	current = tokens_head;
// 	while (current)
// 	{
// 		next = current->next;
// 		free_token(current);
// 		current = next;
// 	}
// }

// static void free_cmd_table(t_cmd_table *cmd_table)
// {
// 	int	i;

// 	i = 0;
// 	if (!cmd_table)
// 		return ;
// 	while (i < cmd_table->cmd_count)
// 	{
// 		free_cmd(cmd_table->cmds[i]);
// 		i++;
// 	}
// 	// ? free(cmd_table ->cmd)? cmd_table is outside the loop, pre malloced in the init
// }

static void	free_shell_struct(t_shell *shell)
{
	printf("only after exit \n");
	if (shell)
	{
		free(shell->cmd_table);
		free_2d_array(shell->envp);
		if (shell->builtin_child)
			free(shell->builtin_child);
		if (shell->builtin_main)
			free(shell->builtin_main);
		free(shell);
	}
}

void	free_shell(t_shell *shell, bool close_shell)
{
	// TODO reset tokens
	// TODO reset cmd_table
	// if (shell->tokens)
	// 	free_tokens(shell->tokens);
	// if (shell->cmd_table)
	// 	free_cmd_table(shell->cmd_table);
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (close_shell == true)
		free_shell_struct(shell);
}

static void	lexer_finish(t_shell *shell)
{
	shell->single_quote = 0;
	shell->double_quote = 0;
}

void	free_2d_array(char **array)
{
	int	i;

	if (array)
	{
		i = 0;
		while (array[i])
		{
			free(array[i]);
			array[i] = NULL;
			i++;
		}
		free(array);
	}
}

void	shell_finish(t_shell *shell)
{
	lexer_finish(shell);
	dup2(shell->original_stdin, STDIN_FILENO);
	free_shell(shell, false);
	should_print("\n--------------------End--------------------\n\n", shell->print_output);
}
