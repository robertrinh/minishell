/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_messages.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/10 17:49:51 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/06/21 18:33:38 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	show_error_message(char *error, t_shell *shell, char *arg, int exit_code)
{
	write(STDERR_FILENO, C_RED, ft_strlen(C_RED));
	write(STDERR_FILENO, "[minishell]: ", 13);
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, RESET_COLOR, ft_strlen(RESET_COLOR));
	write(STDERR_FILENO, "\n", 1);
	shell->exit_code = exit_code;
	return (FAILURE);
}

int	exit_with_message(char *error, t_shell *shell, int exit_code)
{
	write(STDERR_FILENO, C_RED, ft_strlen(C_RED));
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO, RESET_COLOR, ft_strlen(RESET_COLOR));
	write(STDERR_FILENO, "\n", 1);
	shell->exit_code = exit_code;
	exit(shell->exit_code);
	return (FAILURE);
}
