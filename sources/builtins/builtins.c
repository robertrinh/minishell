/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/01 14:47:56 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/06/21 18:38:41 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_shell	*init_main_builtins(t_shell *shell)
{
	int			i;
	t_builtin	builtin_table[B_NUM_MAIN];

	i = 0;
	builtin_table[B_EXIT].name = "exit";
	builtin_table[B_EXIT].function = exit_shell;
	builtin_table[B_CD].name = "cd";
	builtin_table[B_CD].function = cd;
	builtin_table[B_EXPORT].name = "export";
	builtin_table[B_EXPORT].function = export;
	builtin_table[B_UNSET].name = "unset";
	builtin_table[B_UNSET].function = unset;
	shell->builtin_main = safe_malloc(B_NUM_MAIN * sizeof(t_builtin), shell);
	while (i < B_NUM_MAIN)
	{
		shell->builtin_main[i] = builtin_table[i];
		i++;
	}
	return (shell);
}

t_shell	*init_child_builtins(t_shell *shell)
{
	int			i;
	t_builtin	builtin_table[B_NUM_CHILD];

	i = 0;
	builtin_table[B_ECHO].name = "echo";
	builtin_table[B_ECHO].function = echo;
	builtin_table[B_ENV].name = "env";
	builtin_table[B_ENV].function = env;
	builtin_table[B_PWD].name = "pwd";
	builtin_table[B_PWD].function = pwd;
	shell->builtin_child = safe_malloc(B_NUM_CHILD * sizeof(t_builtin), shell);
	while (i < B_NUM_CHILD)
	{
		shell->builtin_child[i] = builtin_table[i];
		i++;
	}
	return (shell);
}

bool	is_builtin(t_builtin *table, t_cmd *cmd, int num)
{
	int		i;
	size_t	len;

	i = 0;
	if (cmd->value == NULL)
		return (false);
	while (i < num)
	{
		len = ft_strlen(table[i].name);
		if (len != ft_strlen(cmd->value))
		{
			i++;
			continue ;
		}
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
			shell->exit_code = table[i].function(cmd, shell);
			return (shell->exit_code);
		}
		i++;
	}
	return (1);
}
