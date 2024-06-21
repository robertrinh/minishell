/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/14 14:04:02 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/06/21 15:01:33 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**alloc_envp(char **envp)
{
	int		i;
	char	**copy_envp;

	i = 0;
	copy_envp = safe_malloc(sizeof(char *) * env_size(envp) + 1);
	while (envp[i])
	{
		copy_envp[i] = safe_strdup(envp[i]);
		i++;
	}
	copy_envp[i] = NULL;
	return (copy_envp);
}

static t_cmd_table	*init_cmd_table(void)
{
	t_cmd_table	*cmd_table;

	cmd_table = safe_malloc(sizeof(t_cmd_table));
	cmd_table->cmd_count = 0;
	cmd_table->cmds = NULL;
	return (cmd_table);
}

bool	save_command(char *command, t_shell *shell)
{
	if (command)
		add_history(command);
	shell->input = safe_strdup(command);
	return (SUCCESS);
}

t_shell	*construct_shell(t_shell *shell, char **envp, char **argv)
{
	shell = safe_malloc(sizeof(t_shell));
	shell->input = NULL;
	shell->tokens = NULL;
	shell->cmd_table = init_cmd_table();
	shell->envp = alloc_envp(envp);
	shell->original_stdin = dup(STDIN_FILENO);
	shell->print_output = argv[1] && ft_strncmp(argv[1], PRINT_FLAG, 2) == 0;
	shell->exit_code = 0;
	shell = init_main_builtins(shell);
	shell = init_child_builtins(shell);
	return (shell);
}

t_shell	*shell_pre_init(t_shell *shell, char **envp, char **argv)
{
	shell = construct_shell(shell, envp, argv);
	return (shell);
}
