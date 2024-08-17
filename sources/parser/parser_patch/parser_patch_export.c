/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_patch_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:16:34 by quentin           #+#    #+#             */
/*   Updated: 2024/08/17 15:42:51 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
# define EXPORT_STRING "export"

static bool join_export_args(t_shell *shell, t_cmd *cmd)
{
    int     i;
    char    **buffer;

    i = 0;
    buffer = safe_malloc((sizeof(char *) * 2), shell);
    buffer[0] = safe_strdup(cmd->args[0], shell);
    i++;
    while (i < cmd->arg_count)
    {
        buffer[0] = ft_strjoin(buffer[0], cmd->args[i]);
        i++;
    }

    free_2d_array(cmd->args);
    cmd->args = buffer;
    return (SUCCESS);
}

static bool will_joing_export_args(t_shell *shell, t_cmd *cmd)
{
    int     export_len;

    export_len = ft_strlen(EXPORT_STRING);
    // if (ft_strlen(cmd->value) != export_len)
    //     return (FAILURE);
    // if (cmd->arg_count >= 1)
    //     return (FAILURE);
    if (ft_strncmp(cmd->value, EXPORT_STRING, ft_strlen(EXPORT_STRING)) == 0)
    {
        join_export_args(shell, cmd);
        return (SUCCESS);
    }
    return (FAILURE);
}

bool should_patch_expot(t_shell *shell)
{
    int     i;
    t_cmd   **cmds;

    i = 0;
    cmds = shell->cmd_table->cmds;

    while (i < shell->cmd_table->cmd_count)
    {
        will_joing_export_args(shell, cmds[i]);
        i++;
    }
    return (SUCCESS);
}
