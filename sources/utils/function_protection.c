/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_protection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:21:05 by qbeukelm          #+#    #+#             */
/*   Updated: 2024/02/29 13:58:01 by qbeukelm         ###   ########.fr       */
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
		exit_with_message(ERROR_MALLOC, RED, 2);
	}
	return (ptr);
}
