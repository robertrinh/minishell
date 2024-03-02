/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/02 14:17:42 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/02 15:29:21 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	restore_prompt(int signal_process)
{
	if (signal_process == SIGINT)
	{
		// rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 1;
	}
}

/*
	tcgetattr:
	Fetches the current terminal attributes for the standard input and stores
	them in termios.

	c_lflag:
	Modify the local mode flags in termios. Turn off the ECHOCTL flag, which
	controls the echoing of control characters. If the flag is set, control
	characters (such as Ctrl+C) are displauted as `^C`.

	tcsetattr:
	Modify the termios attributes for stdin. The TCSAFLUSH flag specifies that
	the change occurs after all output has been transmitted and all input
	read.
*/

void	handle_signals(t_signal signal_process)
{
	struct termios	termios_struct;

	tcgetattr(STDIN_FILENO, &termios_struct);
	termios_struct.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_struct);

	if (signal_process == PARENT)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}

	if (signal_process == CHILD)
	{

	}

	if (signal_process == HEREDOC)
	{

	}
}
