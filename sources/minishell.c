/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 13:13:49 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/01/18 14:48:53 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	retrieve_command(t_shell *shell)
{
	char	*command;

	command = readline(CYELLOW "[minishell]: " RESET_COLOR);
	if (command == NULL)
	{
		// TODO clean_exit()
		return (FAILURE);
	}
	save_command(command, shell);
	return (SUCCESS);
}

static bool	run(t_shell *shell)
{
	while (1)
	{
		retrieve_command(shell);
		if (lexer_manager(shell) == SUCCESS)
		{
			finish_command(shell);
			print_token(shell->tokens);
		}
		//parse();
		tokens_to_tree(shell->tokens);
		printf("\n--------------------End--------------------\n\n");
	}
	return (SUCCESS); // <- Return status to main
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = shell_init();
	run(shell);
	printf("argc: %d, %p, %p", argc, argv, envp);
	return (0);
}
