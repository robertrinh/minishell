/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/01 14:47:56 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/04/06 16:58:49 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_main_builtins(t_shell *shell)
{
	int					i;
	t_builtin			*builtin_table;

	i = 0;
	builtin_table[B_EXIT].name = "exit";
	builtin_table[B_EXIT].function = exit_shell;
	builtin_table[B_CD].name = "cd";
	builtin_table[B_CD].function = cd;
	builtin_table[B_EXPORT].name = "export";
	builtin_table[B_EXPORT].function = export;
	builtin_table[B_UNSET].name = "unset";
	builtin_table[B_UNSET].function = unset;
	shell->builtin_main = safe_malloc(B_NUM_MAIN * sizeof(t_builtin));
	while (i < B_NUM_MAIN)
	{
		shell->builtin_main[i] = builtin_table[i];
		i++;
	}
}

void	init_child_builtins(t_shell *shell)
{
	int					i;
	t_builtin			*builtin_table;

	i = 0;
	builtin_table[B_ECHO].name = "echo";
	builtin_table[B_ECHO].function = echo;
	builtin_table[B_ENV].name = "env";
	builtin_table[B_ENV].function = env;
	builtin_table[B_PWD].name = "pwd";
	builtin_table[B_PWD].function = pwd;
	shell->builtin_child = safe_malloc(B_NUM_CHILD * sizeof(t_builtin));
	while (i < B_NUM_CHILD)
	{
		shell->builtin_child[i] = builtin_table[i];
		i++;
	}
}

bool	is_builtin(t_builtin *table, t_cmd *cmd, int num)
{
	int	i;
	int	len;

	i = 0;
	while (i < num)
	{
		len = ft_strlen(table[i].name);
		if (ft_strncmp(cmd->value, table[i].name, len) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	exec_builtin(t_builtin *table, t_cmd *cmd, t_shell *shell, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (ft_strncmp(cmd->value, table[i].name, ft_strlen(cmd->value)) == 0)
		{
			g_exit_code = table[i].function(cmd, shell);
			return (g_exit_code);
		}
		i++;
	}
	return (1);
}
