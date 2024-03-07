/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:45:44 by qbeukelm          #+#    #+#             */
/*   Updated: 2024/03/07 14:57:22 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int  env(t_cmd* cmd, t_shell *shell)
{
	int i;
	char **envp;
	i = 0;
	envp = shell->envp;
	if (envp == NULL)
		return (1); //!error message no envp found
	while(envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	exit(0);
}