/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:04:02 by qtrinh            #+#    #+#             */
/*   Updated: 2024/02/08 15:57:52 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_cmd	*cmd_init(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
	{
		// TODO clean_exit()
	}
	return (cmd);
}

static int		count_substrings(char **strings)
{
	int		i;

	i = 0;
	while (strings[i])
		i++;
	return (i);
}

static char **alloc_envp(char **envp)
{
	int		i;
	char	**copy_envp;

	i = 0;
	copy_envp = malloc(sizeof(char *) * count_substrings(envp)); // TODO protect
	while (envp[i])
	{
		copy_envp[i] = ft_strdup(envp[i]); // TODO protect
		i++;
	}
	copy_envp[i] = 0;
	return (copy_envp);
}

int		temp_arg_func(t_shell *shell, t_ast_node *ast)
{
	return (0);
};

HANDLE_FUNCTIONS *init_functions(void)
{
	HANDLE_FUNCTIONS	*exec_funcs;

	exec_funcs = malloc(sizeof(HANDLE_FUNCTIONS) * NONE);
	if (exec_funcs == NULL)
	{
		// TODO clean_exit()
	}

	exec_funcs[COMMAND] = execute_command;
	exec_funcs[ARGUMENT] = temp_arg_func;
	exec_funcs[PIPE] = execute_pipe;
	return (exec_funcs);
}

t_shell	*shell_init(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (shell == NULL)
	{
		// TODO clean_exit()
	}
	shell->cmd = cmd_init();
	shell->envp = alloc_envp(envp);
	shell->exec_funcs = init_functions();
	return (shell);
}

bool	save_command(char *input, t_shell *shell)
{
	shell->input = ft_calloc(sizeof(char), ft_strlen(input) + 1);
	if (shell->input == NULL)
	{
		// TODO clean_exit()
		return (FAILURE);
	}
	shell->input = input;
	return (SUCCESS);
}

t_split	*init_split(t_shell *shell, t_split *split)
{
	split->input = malloc(sizeof(char) * ft_strlen(shell->input) + 1);
	if (split->input == NULL)
	{
		// TODO clean_exit()
	}
	split->input = shell->input;
	split->len = ft_strlen(shell->input);
	split->i = 0;
	split->i_check = 0;
	split->count = 0;
	split->i_buff = 0;
	split->i_str = 0;
	split->strings = 0;
	return (split);
}
