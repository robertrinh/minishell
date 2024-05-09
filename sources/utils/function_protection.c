/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_protection.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/29 13:21:05 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/05/09 15:58:41 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/error_messages.h"
#include "../../includes/minishell.h"

void	*safe_strjoin(const char *s1, const char *s2)
{
	void	*ptr;

	ptr = ft_strjoin(s1, s2);
	if (ptr == NULL)
	{
		g_exit_code = EXIT_FAILURE;
		exit_with_message(E_MALLOC, C_RED, g_exit_code);
	}
	return (ptr);
}

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
