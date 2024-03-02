/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/01 16:46:40 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/03/02 14:14:32 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//! -n -> do not output the trailing newline
static bool	find_n_flag(char *str)
{
	int	i;

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

static void	print_echo(t_cmd *cmd)
{
	int	i;
	int	j;
	bool	flag;

	i = 0;
	j = 0;
	flag = false;
	while (cmd->args[i][j] && find_n_flag(&cmd->args[i][j])) //* look at this later
	{
		flag = true;
		j++;
	}
	if (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		i++;
	}
	if (cmd->arg_count == 1)
		return ;
	while (cmd->args[i])
	{
		write(1, " ", 2);
		ft_putstr_fd(cmd->args[i], 1);
		i++;
	}
	if (flag == false)
		write(1, "\n", 3);
	// ! incomplete work
	// TODO fix the -n flag writing
}

bool	ft_echo(t_cmd *cmd)
{
	if (cmd->arg_count == 0)
		return (FAILURE);
	if (cmd->arg_count > 0)
		print_echo(cmd);
	return (SUCCESS);
}
