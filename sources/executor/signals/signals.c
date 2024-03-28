/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/02 14:17:42 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/28 18:29:14 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/* Signal handler for SIGINT (Ctrl-C) in the parent process. */
void	signal_reset_prompt(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit_code = 130; // ! exit code 130 on linux bash
	}
}

/* Signal handler for SIGINT (Ctrl-C) in a child process. */
void	signal_ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_exit_code = 130; // ! exit code 130 on mac bash
	}
}

/* Signal handler for SIGQUIT (Ctrl-\) in a child process. */
void	signal_backslash(int sig)
{
	if (sig == SIGQUIT)
	{
		//write(STDERR_FILENO, "Child signal\n", 14); // ? test regarding heredoc/child signals
		write(STDERR_FILENO, "Quit\n", 5);
		g_exit_code = 131; // ! exit code 131 on mac bash
	}
}

/* Signal handler for SIGINT (Ctrl-c) in the heredoc process. */
void	signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		g_exit_code = 1;
		exit(g_exit_code); // ! exit code 1 on mac bash
	}
}

//TODO signals reset after heredoc?
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
	if (signal_process == CHILD)
	{
		tcgetattr(STDIN_FILENO, &termios_struct);
		termios_struct.c_lflag |= ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_struct);
		signal(SIGINT, signal_ctrl_c);
		signal(SIGQUIT, signal_backslash);
	}
	if (signal_process == HEREDOC)
	{
		signal(SIGINT, signal_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}

