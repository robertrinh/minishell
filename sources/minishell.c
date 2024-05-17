/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/03 13:13:49 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/05/17 14:20:20 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_exit_code = 0;

static bool	shell_retrieve_command(t_shell *shell)
{
	char	*command;

	command = readline(C_YELLOW "[minishell]: " RESET_COLOR);
	if (command == NULL)
	{
		free(command);
		free_shell(shell, true);
		exit_with_message(E_EOF_DESCRIPTOR, RESET_COLOR, EXIT_SUCCESS);
	}
	save_command(command, shell);
	free(command);
	return (SUCCESS);
}

static bool	shell_run(t_shell *shell)
{
	while (1)
	{
		shell = shell_run_init(shell);
		shell_retrieve_command(shell);
		if (shell->input[0] == '\0')
		{
			shell_finish(shell);
			continue ;
		}
		shell_lexer(shell);
		if (shell_parser(shell) == SUCCESS)
			shell_execute(shell);
		shell_finish(shell);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		*shell;

	(void) argc;
	shell = NULL;
	shell = shell_pre_init(shell, envp, argv);
	shell_run(shell);
	return (EXIT_SUCCESS);
}
