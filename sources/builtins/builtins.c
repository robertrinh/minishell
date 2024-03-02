/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/01 14:47:56 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/03/02 14:14:27 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (true);
	// if (ft_strncmp(cmd, "cd", 3) == 0)
	// 	return (true);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (true);
	// if (ft_strncmp(cmd, "export", 7) == 0)
	// 	return (true);
	// if (ft_strncmp(cmd, "unset", 6) == 0)
	// 	return (true);
	// if (ft_strncmp(cmd, "env", 4) == 0)
	// 	return (true);
	// if (ft_strncmp(cmd, "exit", 5) == 0)
	// 	return (true);
	return (false);
}

bool	exec_builtin(t_cmd *cmd)
{
	int	exit_status = 0; //TODO signal

	if (ft_strncmp(cmd->value, "echo", 5) == 0)
		exit_status = ft_echo(cmd);
	// else if (ft_strncmp(cmd->value, "cd", 3) == 0)
	// 	exit_status = ft_cd();
	else if (ft_strncmp(cmd->value, "pwd", 4) == 0)
		exit_status = ft_pwd();
	// else if (ft_strncmp(cmd->value, "export", 7) == 0)
	// 	exit_status = ft_export();
	// else if (ft_strncmp(cmd->value, "unset", 6) == 0)
	// 	exit_status = ft_unset();
	// else if (ft_strncmp(cmd->value, "env", 4) == 0)
	// 	exit_status = ft_env();
	// else if (ft_strncmp(cmd->value, "exit", 5) == 0)
	// 	exit_status = ft_exit();
	// else
		return (false);
	return (true);
}
