/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:17:42 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/03/07 14:31:49 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/* Signal handler for SIGINT (Ctrl-C) in the parent process. */
void	signal_reset_prompt(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 1;
	}
}

/* Signal handler for SIGINT (Ctrl-C) in a child process. */
void signal_ctrl_c(int sig)
{
    if (sig == SIGINT)
    {
        ft_putchar_fd('\n', STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		signal(SIGQUIT, SIG_IGN);
        g_exit_status = sig + 128;
    }
}

/* Signal handler for SIGQUIT (Ctrl-\). */
void signal_backslash(int sig)
{
    if (sig == SIGQUIT)
    {
        ft_putstr_fd("Quit: ", STDERR_FILENO);
        ft_putnbr_fd(sig, STDERR_FILENO);
        ft_putchar_fd('\n', STDERR_FILENO);
        g_exit_status = sig + 128;
    }
}

/* Display here_doc sign (>) and exit the process on SIGINT. */
void signal_heredoc(int sig)
{
    if (sig == SIGINT)
    {
        rl_replace_line("", 0);
		// rl_replace_line("", 0);
        // ft_putchar_fd('\n', STDOUT_FILENO);
        // rl_on_new_line();
        exit(g_exit_status = 1);
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
		signal(SIGINT, signal_reset_prompt);
		signal(SIGQUIT, SIG_IGN);
	}

	// if (signal_process == CHILD)
	// {
	// 	tcgetattr(STDIN_FILENO, &termios_struct);
	// 	termios_struct.c_lflag |= ECHOCTL;
	// 	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_struct);
	// 	signal(SIGINT, signal_ctrl_c);
	// 	signal(SIGQUIT, signal_backslash);
	// }

	// if (signal_process == HEREDOC)
	// {
	// 	signal(SIGINT, signal_heredoc);
    //     signal(SIGQUIT, SIG_IGN);
	// }
}
