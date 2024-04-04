/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/03 13:13:49 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/04/04 16:44:15 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_exit_code = 0;

static bool	retrieve_command(t_shell *shell)
{
	char	*command;

	command = readline(CYELLOW "[minishell]: " RESET_COLOR);
	if (command == NULL)
	{
		write(1, "readline NULL\n", 16);
		exit(0);
	}
	save_command(command, shell);
	if (command)
		add_history(command);
	return (SUCCESS);
}

static bool	run(t_shell *shell)
{
	while (1)
	{
		handle_signals(PARENT);
		retrieve_command(shell);
		if (shell->input[0] == '\0')
		{
			free(shell->input);
			continue ;
		}
		if (lexer_manager(shell) == SUCCESS)
		{
			finish_lexer(shell);
			if (shell->print_output)
				print_tokens(shell->tokens);
		}
		parse(shell);
		execute(shell);
		should_print("\n--------------------End--------------------\n\n", shell->print_output);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void) argc;
	shell = shell_init(envp, argv);
	run(shell);
	return (EXIT_SUCCESS);
}
