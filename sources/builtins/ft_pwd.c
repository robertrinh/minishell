/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/01 18:57:33 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/03/02 14:14:40 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_pwd(void)
{
	// * getcwd
	// ! when building cd, have to update pwd with oldpwd / pwd @ env but should implement at cd
	char	*buf;

	buf = getcwd(NULL, 0);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	return (SUCCESS);
}
