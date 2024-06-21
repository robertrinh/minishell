/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_protection.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/29 13:21:05 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/06/21 17:22:58 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/error_messages.h"
#include "../../includes/minishell.h"

void	*safe_strjoin(const char *s1, const char *s2, t_shell *shell)
{
	void	*ptr;

	ptr = ft_strjoin(s1, s2);
	if (ptr == NULL)
		exit_with_message(E_MALLOC, shell, EXIT_FAILURE);
	return (ptr);
}

void	*safe_malloc(size_t size, t_shell *shell)
{
	void	*ptr;

	ptr = NULL;
	ptr = malloc(size);
	if (ptr == NULL)
	{
		free (ptr);
		exit_with_message(E_MALLOC, shell, EXIT_FAILURE);
	}
	return (ptr);
}

void	*safe_calloc(size_t count, size_t size, t_shell *shell)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (ptr == NULL)
		exit_with_message(E_MALLOC, shell, EXIT_FAILURE);
	return (ptr);
}

char	*safe_strdup(char *str, t_shell *shell)
{
	char	*p;

	if (str == NULL)
		return (str);
	p = ft_strdup(str);
	if (p == NULL)
	{
		exit_with_message(E_MALLOC, shell, EXIT_FAILURE);
		return (NULL);
	}
	return (p);
}

char	*safe_strdup_from(const char *str, int i, t_shell *shell)
{
	char	*p;

	p = ft_strdup_from(str, i);
	if (p == NULL)
		exit_with_message(E_MALLOC, shell, EXIT_FAILURE);
	return (p);
}
