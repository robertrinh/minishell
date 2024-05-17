/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_messages.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/10 17:49:51 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/05/10 17:55:50 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/error_messages.h"
#include "../../includes/minishell.h"

void	arg_error(void)
{
	g_exit_code = EXIT_FAILURE;
	write(STDERR_FILENO, "minishell: exit: too many arguments\n", 37);
}

void	numeric_error(char *str)
{
	g_exit_code = X_NUMERIC_ERR;
	write(STDERR_FILENO, "minishell: exit: ", 18);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, ": numeric argument required\n", 29);
}

int	show_error_message(char *error, char *color, char *arg, int exit_code)
{
	write(STDERR_FILENO, color, ft_strlen(color));
    write(STDERR_FILENO, "minishell: ", 12);
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
}
