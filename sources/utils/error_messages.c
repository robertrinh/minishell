/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_messages.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/10 17:49:51 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/06/13 16:40:11 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	show_error_message(char *error, char *color, char *arg, int exit_code)
{
	write(STDERR_FILENO, color, ft_strlen(color));
	write(STDERR_FILENO, "[minishell]: ", 13);
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, RESET_COLOR, ft_strlen(RESET_COLOR));
	write(STDERR_FILENO, "\n", 1);
	g_exit_code = exit_code;
	return (FAILURE);
}

int	exit_with_message(char *error, char *color, int exit_code)
{
	write(STDERR_FILENO, color, ft_strlen(color));
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO, RESET_COLOR, ft_strlen(RESET_COLOR));
	write(STDERR_FILENO, "\n", 1);
	g_exit_code = exit_code;
	exit(g_exit_code);
	return (FAILURE);
}
