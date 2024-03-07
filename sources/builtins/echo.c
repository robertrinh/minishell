/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:45:13 by qbeukelm          #+#    #+#             */
/*   Updated: 2024/03/07 14:58:25 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//! -n -> do not output the trailing newline
static bool find_n_flag(char *str)
{
    int i;
    i = 0;
    if (str[i] == '-')
    {
        i++;
        while (str[i])
        {
            if (str[i] == 'n')
                return (true);
            i++;
        }
        return (false);
    }
    return (false);
}

static void print_echo(t_cmd *cmd)
{
    int i;
    bool    flag;
    
    i = 0;
    flag = false;
    while (cmd->args[i] && find_n_flag(cmd->args[i]))
    {
        flag = true;
        i++;
    }
    while (cmd->args[i])
    {
        write(1, cmd->args[i], ft_strlen(cmd->args[i]));
        if (cmd->args[i + 1])
            write(1, " ", 2);
        i++;
    }
    if (flag == false)
        write(1, "\n", 1);
} //! at one args, it has trash value

int echo(t_cmd *cmd, t_shell *shell)
{
    if (cmd->arg_count == 0)
        return (FAILURE);
    if (cmd->arg_count > 0)
        print_echo(cmd);
	should_print("pointer %p\n", shell->print_output);
    exit(0);
}
