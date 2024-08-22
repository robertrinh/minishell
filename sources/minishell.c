/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 13:13:49 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/08/21 13:39:48 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal = 0;

static void	shell_signal_check(t_shell *shell)
{
	if (g_signal == SIGINT)
	{
		shell->exit_code = 130;
		g_signal = 0;
	}
}

static t_validation	is_valid_input(t_shell *shell)
{
	if (shell->input[0] == '\0')
		return (FAILURE);
	return (SUCCESS);
}

static bool	shell_retrieve_command(t_shell *shell)
{
	char	*command;

	command = readline(C_YELLOW "[minishell]: " RESET_COLOR);
	if (command == NULL)
	{
		free(command);
		free_shell(shell, true);
	}
	save_command(command, shell);
	free(command);
	return (SUCCESS);
}

static bool	shell_run(t_shell *shell)
{
	while (1)
	{
		handle_signals(PARENT);
		shell_retrieve_command(shell);
		shell_signal_check(shell);
		if (is_valid_input(shell))
			if (shell_lexer(shell))
				if (shell_parser(shell))
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
