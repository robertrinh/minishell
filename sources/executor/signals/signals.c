/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:17:42 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/03/07 17:51:25 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/* Signal handler for SIGINT (Ctrl-C) in the parent process. */
void	signal_reset_prompt(int sig)
{
	printf("parent signal: %d\n", sig);
}

/* Signal handler for SIGINT (Ctrl-C) in a child process. */
void signal_ctrl_c(int sig)
{
	printf("child signal: %d\n", sig);
}

void	handle_signals(t_signal signal_process)
{
	struct termios	termios_struct;

	tcgetattr(STDIN_FILENO, &termios_struct);
	termios_struct.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_struct);

	if (signal_process == PARENT)
	{
		signal(SIGINT, signal_reset_prompt);
		signal(SIGINT, SIG_IGN);
	}

	if (signal_process == CHILD)
	{
		signal(SIGINT, signal_ctrl_c);
	}
}
