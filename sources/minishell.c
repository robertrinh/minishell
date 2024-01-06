/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 13:13:49 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/01/06 12:06:12 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static char	*retrieve_command(void)
{
	char *command;

	command = readline("[minishell]: ");
	if (command == NULL)
	{
		// TODO Free
	}
	return (command);
}

void	print_token(t_token *tokens)
{
	printf("\n\n========print tokens========\n");
	while (tokens)
	{
		printf("%s \n", tokens->value);
		tokens = tokens->next;
	}
}

static void	finish_command(t_shell *shell)
{
	shell->cmd->single_quote = 0;
	shell->cmd->double_quote = 0;
}

static bool	run(t_shell *shell)
{
	char	*command;
	t_token	*tokens_head;

	tokens_head = NULL;
	while (1) 
	{
		command = retrieve_command();
		input_init(command, shell);
		tokens_head = tokens_builder_manager(shell);
		finish_command(shell);
		print_token(shell->tokens);

		printf("\n--------------------End--------------------\n\n");
	}
	return (true);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = shell_init();
	run(shell);

	// print uncsured param
	printf("argc: %d, %p, %p", argc, argv, envp);
	// init data
	// Store params
	// run
	return (0);
}
