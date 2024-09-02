/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:04:02 by qtrinh            #+#    #+#             */
/*   Updated: 2024/09/02 13:30:30 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**alloc_envp(char **envp, t_shell *shell)
{
	int		i;
	char	**copy_envp;

	i = 0;
	copy_envp = safe_malloc(sizeof(char *) * env_size(envp) + 1, shell);
	while (envp[i])
	{
		copy_envp[i] = safe_strdup(envp[i], shell);
		i++;
	}
	copy_envp[i] = NULL;
	return (copy_envp);
}

static t_cmd_table	*init_cmd_table(t_shell *shell)
{
	t_cmd_table	*cmd_table;

	cmd_table = safe_malloc(sizeof(t_cmd_table), shell);
	cmd_table->cmd_count = 0;
	cmd_table->cmds = NULL;
	return (cmd_table);
}

bool	save_command(char *command, t_shell *shell)
{
	if (command)
		add_history(command);
	shell->input = safe_strdup(command, shell);
	return (SUCCESS);
}

t_shell	*construct_shell(t_shell *shell, char **envp, char **argv)
{
	shell = malloc(sizeof(t_shell));
	if (shell == NULL)
		return (NULL);
	shell->exit_code = 0;
	shell->input = NULL;
	shell->tokens = NULL;
	shell->split = NULL;
	shell->cmd_table = init_cmd_table(shell);
	shell->envp = alloc_envp(envp, shell);
	shell->original_stdin = dup(STDIN_FILENO);
	shell->print_output = argv[1] && ft_strncmp(argv[1], PRINT_FLAG, 2) == 0;
	return (shell);
}

t_shell	*shell_pre_init(t_shell *shell, char **envp, char **argv)
{
	shell = construct_shell(shell, envp, argv);
	return (shell);
}
