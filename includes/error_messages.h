/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_messages.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 20:04:35 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/24 17:34:57 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGES_H
# define ERROR_MESSAGES_H

# include "minishell.h"

// Show error message
# define E_QUOTE				"unmatched quote."
# define E_PIPE					"unmatched pipe."
# define E_REDIRECT				"unmatched redirect."
# define E_MALLOC				"malloc: failed to malloc."
# define E_EOF_DESCRIPTOR		"exit"
# define E_OPERATOR				"invalid operator."
# define E_FORK					"fork failure."
# define E_EXPORT				"export: not a valid identifier: "
# define E_EXECVE				"execve: command not found: "
# define E_NO_FILE_DIR			"No such file or directory: "
# define E_DUP					"dup failure: "
# define E_WAITPID				"waitpid failure."
# define E_PIPE_FAIL			"pipe failure: "
# define E_CLOSE				"close failure"
# define E_OPENING_FILE			"could not open file: "
# define E_DENY					"Permission denied: "
# define E_NOT_A_DIR			"Not a directory: "
# define E_CMD_NOT_FOUND		"command not found: "
# define E_NUMERIC_ERR			"exit: numeric argument required"
# define E_ARG_ERR				"exit: too many arguments"
# define E_CD					"cd: too many arguments"
# define E_OVERFLOW				"split: buffer overflow."

// Exit codes
# define X_FAILURE				EXIT_FAILURE
# define X_NUMERIC_ERR			2
# define X_SIG_HEREDOC			130
# define X_SIG_CTRL_C			130
# define X_SIG_BACKSLASH		131
# define X_CMD					127

typedef struct s_shell	t_shell;

// error_messages.c
int		show_error_message(char *error, t_shell *shell, char *arg, \
							int exit_code);
int		exit_with_message(char *error, t_shell *shell, int exit_code);

#endif
