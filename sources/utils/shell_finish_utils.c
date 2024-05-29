/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_finish_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/23 16:15:41 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/05/25 22:25:53 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_cmd_fd(t_cmd *cmd)
{
	// * check if fd's are not free'd before
	if (cmd->fd_in)
	{
		free(cmd->fd_in);
		cmd->fd_in = NULL;
	}
	if (cmd->fd_out)
	{
		free(cmd->fd_out);
		cmd->fd_out = NULL;
	}
}

//!			cat tasks.md > grep "a"
//!			'EOF' / "..."
static void	free_args_format_cmd(t_cmd *cmd)
{
	int	i;

	if (cmd->args)
	{
		i = 0;
		while (i < cmd->arg_count)
		{
			if (cmd->args[i])
				free(cmd->args[i]);
			cmd->args[i] = NULL;
			i++;
		}
		free(cmd->args);
		cmd->args = NULL;
	}
	if (cmd->cmd_and_args)
	{
		i = 0;
		while (i <= cmd->arg_count)
		{
			if (cmd->cmd_and_args[i])
				free(cmd->cmd_and_args[i]);
			cmd->cmd_and_args[i] = NULL;
			i++;
		}
		free(cmd->cmd_and_args);
		cmd->cmd_and_args = NULL;
	}
}

static void	free_token(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->value)
	{
		free(token->value);
		token->value = NULL;
	}
	free(token);
	token = NULL;
}

void free_tokens(t_token *token)
{
	t_token *next;

	next = NULL;
	if (token == NULL)
		return ;
	while (token)
	{
		next = token->next;
		free_token(token);
		token = next;
	}
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	
	free_args_format_cmd(cmd);
	free_cmd_fd(cmd);
	
	if (cmd->cmd_path)
	{
		free(cmd->cmd_path);
		cmd->cmd_path = NULL;
	}
	free(cmd);
}

void	free_2d_array(char **array)
{
	int	i;

	if (array)
	{
		i = 0;
		while (array[i])
		{
			free(array[i]);
			array[i] = NULL;
			i++;
		}
		free(array);
	}
}

