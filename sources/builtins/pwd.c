/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/01 18:57:33 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/04/06 16:51:41 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(t_cmd *cmd, t_shell *shell)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	return (0);
}
// ! when building cd, have to update pwd with oldpwd / pwd @ env but should implement at cd
