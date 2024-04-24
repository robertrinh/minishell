/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/02 14:17:42 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/04/23 21:02:02 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/* 
	Signal handler for SIGINT (Ctrl-C) in the parent process. 
*/
void	signal_reset_prompt(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit_code = X_SIG_CTL_C;
	}
}

/* 
	Signal handler for SIGINT (Ctrl-C) in a child process.
 */
void	signal_ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		g_exit_code = X_SIG_CTL_C;
	}
}

/*
	Signal handler for SIGQUIT (Ctrl-\) in a child process. 
*/
void	signal_backslash(int sig)
{
	if (sig == SIGQUIT)
	{
		write(STDERR_FILENO, "Quit\n", 5);
		g_exit_code = X_SIG_BACKSLASH;
	}
}

/* 
	Signal handler for SIGINT (Ctrl-c) in the heredoc process.
*/
void	signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		g_exit_code = X_SIG_HEREDOC;
		exit(g_exit_code);
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
