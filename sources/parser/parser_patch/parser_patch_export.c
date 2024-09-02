/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_patch_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:16:34 by quentin           #+#    #+#             */
/*   Updated: 2024/09/02 13:48:35 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#define EXPORT_STRING "export"

static bool	join_export_args(t_shell *shell, t_cmd *cmd)
{
	int		i;
	char	**buffer;
	char	*joint_buffers;

	i = 0;
	buffer = safe_malloc((sizeof(char *) * 2), shell);
	buffer[0] = safe_strdup(cmd->args[0], shell);
	i++;
	while (i < cmd->arg_count)
	{
		joint_buffers = ft_strjoin(buffer[0], cmd->args[i]);
		free(buffer[0]);
		buffer[0] = joint_buffers;
		i++;
	}
	free_2d_array(cmd->args);
	cmd->args = buffer;
	cmd->arg_count = 1;
	return (SUCCESS);
}

/*
	Do not merge export args if there are meant to be
	multiple args. i.e. "export a=1 b=2"
*/
static bool	contains_multiple_export_delimiters(t_cmd *cmd)
{
	int	i;
	int	delimiter_count;

	i = 0;
	delimiter_count = 0;
	while (i < cmd->arg_count)
	{
		if (ft_strrchr(cmd->args[i], EXPORT_DELIMITER))
			delimiter_count++;
		i++;
	}
	if (delimiter_count > 1)
		return (true);
	return (false);
}

static bool	will_join_export_args(t_shell *shell, t_cmd *cmd)
{
	size_t	export_len;

	export_len = ft_strlen(EXPORT_STRING);
	if (ft_strlen(cmd->value) != export_len)
		return (FAILURE);
	if (ft_strncmp(cmd->value, EXPORT_STRING, ft_strlen(EXPORT_STRING)) == 0)
	{
		if (contains_multiple_export_delimiters(cmd))
			return (SUCCESS);
		join_export_args(shell, cmd);
		return (SUCCESS);
	}
	return (FAILURE);
}

/*
    If export command contains spaces, these are split into
    multiple args. Merges any split args for export.
*/
bool	should_patch_export(t_shell *shell)
{
	int		i;
	t_cmd	**cmds;

	i = 0;
	cmds = shell->cmd_table->cmds;
	while (i < shell->cmd_table->cmd_count)
	{
		will_join_export_args(shell, cmds[i]);
		i++;
	}
	return (SUCCESS);
}
