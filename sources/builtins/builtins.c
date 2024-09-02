/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:29:42 by qbeukelm          #+#    #+#             */
/*   Updated: 2024/09/02 14:09:10 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

bool	is_main_builtin(char *cmd_value)
{
	if (!cmd_value)
		return (false);
	if (!ft_strncmp(cmd_value, B_MAIN_EXIT, ft_strlen(B_MAIN_EXIT)))
		return (true);
	else if (!ft_strncmp(cmd_value, B_MAIN_CD, ft_strlen(B_MAIN_CD)))
		return (true);
	else if (!ft_strncmp(cmd_value, B_MAIN_EXPORT, ft_strlen(B_MAIN_EXPORT)))
		return (true);
	else if (!ft_strncmp(cmd_value, B_MAIN_UNSET, ft_strlen(B_MAIN_UNSET)))
		return (true);
	return (false);
}

bool	is_child_builtin(char *cmd_value)
{
	if (!cmd_value)
		return (false);
	if (!ft_strncmp(cmd_value, B_CHILD_ECHO, ft_strlen(B_CHILD_ECHO)))
		return (true);
	else if (!ft_strncmp(cmd_value, B_CHILD_ENV, ft_strlen(B_CHILD_ENV)))
		return (true);
	else if (!ft_strncmp(cmd_value, B_CHILD_PWD, ft_strlen(B_CHILD_PWD)))
		return (true);
	return (false);
}

int	exec_builtin(t_shell *shell, t_cmd *cmd)
{
	if (!ft_strncmp(cmd->value, B_MAIN_EXIT, ft_strlen(B_MAIN_EXIT)))
		return (exit_shell(cmd, shell));
	else if (!ft_strncmp(cmd->value, B_MAIN_CD, ft_strlen(B_MAIN_CD)))
		return (cd(cmd, shell));
	else if (!ft_strncmp(cmd->value, B_MAIN_EXPORT, ft_strlen(B_MAIN_EXPORT)))
		return (export(cmd, shell));
	else if (!ft_strncmp(cmd->value, B_MAIN_UNSET, ft_strlen(B_MAIN_UNSET)))
		return (unset(cmd, shell));
	else if (!ft_strncmp(cmd->value, B_CHILD_ECHO, ft_strlen(B_CHILD_ECHO)))
		return (echo(cmd, shell));
	else if (!ft_strncmp(cmd->value, B_CHILD_ENV, ft_strlen(B_CHILD_ENV)))
		return (env(cmd, shell));
	else if (!ft_strncmp(cmd->value, B_CHILD_PWD, ft_strlen(B_CHILD_PWD)))
		return (pwd(cmd, shell));
	return (false);
}
