/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/25 15:59:15 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/04/25 17:08:15 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	free_cmd_fd(t_cmd *cmd)
// {
// 	// * check if fd's are not free'd before
// 	if (cmd->fd_in)
// 		free(cmd->fd_in);
// 	if (cmd->fd_out)
// 		free(cmd->fd_out);
// }

// static void	free_args_format_cmd(t_cmd *cmd)
// {
// 	int	i;

// 	if (cmd->args)
// 	{
// 		i = 0;
// 		while (cmd->args[i])
// 		{
// 			free(cmd->args[i]);
// 			i++;
// 		}
// 		free(cmd->args);
// 	}
// 	if (cmd->formatted_cmd)
// 	{
// 		i = 0;
// 		while (cmd->formatted_cmd[i])
// 		{
// 			free(cmd->formatted_cmd[i]);
// 			i++;
// 		}
// 		free(cmd->formatted_cmd);
// 	}
// }

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	// free_args_format_cmd(cmd);
	// free_cmd_fd(cmd);
	// if (cmd->cmd_path)
	// 	free(cmd->cmd_path);
	// free(cmd);
	// * free cmd->fd's
	// * free args
	// * free formatted cmd
	// * free cmd_path
	// ! free cmd value not needed. tokens value already cleared
}

void	free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->value)
		free(token->value);
	free(token);
}
