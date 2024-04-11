/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_protection.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/29 13:21:05 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/04/08 07:44:28 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/error_messages.h"
#include "../../includes/minishell.h"

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		// TODO correct exit code?
		g_exit_code = EXIT_FAILURE;
		exit_with_message(E_MALLOC, C_RED, g_exit_code);
	}
	return (ptr);
}

void	*safe_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (ptr == NULL)
	{
		// TODO correct exit code?
		g_exit_code = EXIT_FAILURE;
		exit_with_message(E_MALLOC, C_RED, g_exit_code);
	}
	return (ptr);
}

char	*safe_strdup(const char *str)
{
	char	*p;

	p = ft_strdup(str);
	if (p == NULL)
	{
		// TODO correct exit code?
		g_exit_code = EXIT_FAILURE;
		exit_with_message(E_MALLOC, C_RED, g_exit_code);
	}
	return (p);
}

char	*safe_strdup_from(const char *str, int i)
{
	char	*p;

	p = ft_strdup_from(str, i);
	if (p == NULL)
	{
		// TODO correct exit code?
		g_exit_code = EXIT_FAILURE;
		exit_with_message(E_MALLOC, C_RED, g_exit_code);
	}
	return (p);
}
