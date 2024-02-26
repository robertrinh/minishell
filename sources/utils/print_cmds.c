/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_cmds.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/21 21:33:51 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/02/25 19:05:13 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_redirects(t_cmd *cmd)
{
	t_redirect	*fd_in;
	t_redirect	*fd_out;
	t_redirect	*heredoc;

	fd_in = cmd->fd_in;
	while (fd_in)
	{
		printf("\t\t< %s\n", (char *) fd_in->value);
		fd_in = fd_in->next;
	}

	fd_out = cmd->fd_out;
	while (fd_out)
	{
		printf("\t\t> %s\n", (char *) fd_out->value);
		fd_out = fd_out->next;
	}

	heredoc = cmd->heredoc;
	while (heredoc)
	{
		printf("\t\t<< %s\n", (char *) heredoc->value);
		heredoc = heredoc->next;
	}
}

static void	print_cmd(t_cmd **cmds, int i)
{
	int		j;

	j = 0;
	printf("[%d] %s\n", i, cmds[i]->value);
	while (j < cmds[i]->arg_count)
	{
		printf("\t%s\n", cmds[i]->args[j]);
		j++;
	}
	print_redirects(cmds[i]);
	printf("--\n");
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
	printf("\n");
}

void should_print(char *s, bool should_print)
{
	if (should_print)
		printf("%s", s);
}
