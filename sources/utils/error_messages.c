/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_messages.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 20:36:44 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/05/03 15:13:11 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/error_messages.h"
#include "../../includes/minishell.h"

void	arg_error(void)
{
	g_exit_code = EXIT_FAILURE;
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
}

void	numeric_error(char *str)
{
	g_exit_code = X_NUMERIC_ERR;
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

int	show_error_message(char *error, char *color, char *arg, int exit_code)
{
	char	*message;

	message = ft_strjoin(color, "minishell: ");
	message = ft_strjoin(message, error);
	message = ft_strjoin(message, arg);
	message = ft_strjoin(message, RESET_COLOR);
	message = ft_strjoin(message, "\n");
	write(2, message, ft_strlen(message));
	free(message);
	g_exit_code = exit_code;
	return (FAILURE);
}

int	exit_with_message(const char *error, const char *color, int exit_code)
{
	char	*message;

	message = ft_strjoin(color, error);
	message = ft_strjoin(message, RESET_COLOR);
	message = ft_strjoin(message, "\n");
	write(2, message, ft_strlen(message));
	free(message);
	g_exit_code = exit_code;
	exit(g_exit_code);
}
