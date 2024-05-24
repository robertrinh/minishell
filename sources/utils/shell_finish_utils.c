/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_finish_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/23 16:15:41 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/05/23 18:44:51 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	free_cmd_fd(t_cmd *cmd)
// {
// 	// * check if fd's are not free'd before
// 	if (cmd->fd_in)
// 	{
// 		free(cmd->fd_in);
// 		cmd->fd_in = NULL;
// 	}
// 	if (cmd->fd_out)
// 	{
// 		free(cmd->fd_out);
// 		cmd->fd_out = NULL;
// 	}
// }

static void	free_args_format_cmd(t_cmd *cmd)
{
	int	i;

	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			cmd->args[i] = NULL;
			i++;
		}
		free(cmd->args);
	}
	if (cmd->formatted_cmd)
	{
		i = 0;
		while (cmd->formatted_cmd[i])
		{
			free(cmd->formatted_cmd[i]);
			cmd->formatted_cmd[i] = NULL;
			i++;
		}
		free(cmd->formatted_cmd);
	}
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free_args_format_cmd(cmd);
	// free_cmd_fd(cmd);
	if (cmd->cmd_path)
	{
		free(cmd->cmd_path);
		cmd->cmd_path = NULL;
	}
	free(cmd);
}

void	free_token(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->value)
	{
		free(token->value);
		token->value = NULL;
	}
	free(token);
}
