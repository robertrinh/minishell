/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_cmds.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/21 21:33:51 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/05/26 13:57:05 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_fd_in(t_redirect *fd_in)
{
	while (fd_in)
	{
		if (fd_in->type == IN)
		{
			ft_putstr_fd("\t\t<  ", STDOUT_FILENO);
			ft_putstr_fd((char *) fd_in->value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		else if (fd_in->type == IN_APPEND)
		{
			ft_putstr_fd("\t\t<< ", STDOUT_FILENO);
			ft_putstr_fd((char *) fd_in->value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		fd_in = fd_in->next;
	}
}

static void	print_redirects(t_cmd *cmd)
{
	t_redirect	*fd_in;
	t_redirect	*fd_out;

	fd_in = cmd->fd_in;
	print_fd_in(fd_in);
	fd_out = cmd->fd_out;
	while (fd_out)
	{
		ft_putstr_fd("\t\t> ", STDOUT_FILENO);
		ft_putstr_fd((char *) fd_out->value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		fd_out = fd_out->next;
	}
}

static void	print_cmd(t_cmd **cmds, int i)
{
	int		j;

	j = 0;
	ft_putstr_fd("[", STDOUT_FILENO);
	ft_putnbr_fd(i, STDOUT_FILENO);
	ft_putstr_fd("] ", STDOUT_FILENO);
	ft_putstr_fd(cmds[i]->value, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	while (j < cmds[i]->arg_count)
	{
		ft_putstr_fd("\t", STDOUT_FILENO);
		ft_putstr_fd(cmds[i]->args[j], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
        j++;
	}
	print_redirects(cmds[i]);
	ft_putstr_fd("--\n", STDOUT_FILENO);
}

void	print_cmds(t_cmd_table *cmd_table)
{
	int		i;

	i = 0;
	while (i < cmd_table->cmd_count)
	{
		print_cmd(cmd_table->cmds, i);
		i++;
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	should_print(char *s, bool should_print)
{
	if (should_print)
		ft_putstr_fd(s, STDOUT_FILENO);
}
