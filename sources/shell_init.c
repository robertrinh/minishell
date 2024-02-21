/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/14 14:04:02 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/02/21 21:25:44 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static t_cmd_table *init_cmd_table(void)
{
	t_cmd_table		*cmd_table;

	cmd_table = malloc(sizeof(t_cmd_table));
	if (cmd_table == NULL)
	{
		// TODO clean_exit()
	}
	return (cmd_table);
}

t_shell	*shell_init(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (shell == NULL)
	{
		// TODO clean_exit()
	}
	shell->cmd_table = init_cmd_table();
	shell->envp = alloc_envp(envp);
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
