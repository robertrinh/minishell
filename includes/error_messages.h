/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_messages.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 20:04:35 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/04/14 14:00:53 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGES_H
# define ERROR_MESSAGES_H

// Show error message
# define E_QUOTE				"unmatched quote."
# define E_PIPE					"unmatched pipe."
# define E_REDIRECT				"unmatched redirect."
# define E_MALLOC				"malloc failure."
# define E_READLINE_FAILURE		"readline failure."
# define E_OPERATOR				"invalid operator."
# define E_ENV_NOT_FOUND		"enviroment not found."
# define E_FORK					"fork failure."
# define E_PIPE_FAIL			"pipe failure."
# define E_OPENING_FILE			"could not open file: "
# define E_EXPORT				"export: not a valid identifier: "
# define E_CMD					"execve: command not found: "
# define E_CMD_NOT_FOUND		"no such file or directory: "

// Exit codes
# define X_INIT					EXIT_SUCCESS
# define X_QUOTE				EXIT_FAILURE
# define X_PIPE					EXIT_FAILURE
# define X_REDIRECT				EXIT_FAILURE
# define X_MALLOC				EXIT_FAILURE
# define X_READLINE_FAILURE		EXIT_FAILURE
# define X_OPERATOR				EXIT_FAILURE
# define X_OPENING_FILE			EXIT_FAILURE
# define X_EXPORT				EXIT_FAILURE
# define X_NEUMERIC_ERROR		2
# define X_SIG_HEREDOC			1
# define X_SIG_CTL_C			130
# define X_SIG_BACKSLASH		131
# define X_CMD					127

// error_messages.c
int		show_error_message(char *error, char *color, char *arg, int exit_code);
int		exit_with_message(const char *error, const char *color, int exit_code);

#endif
