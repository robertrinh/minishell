/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_post_process.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/16 10:13:21 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/07/25 17:28:13 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	expand_arg(t_cmd *cmd, t_vec *vec, int *i)
{
	char	*expanded_arg;

	expanded_arg = NULL;
	expanded_arg = ft_vec_to_str(vec);
	if (expanded_arg && expanded_arg != cmd->args[*i])
	{
		free(cmd->args[*i]);
		cmd->args[*i] = expanded_arg;
	}
}

static bool	handle_args_expansion(char *arg, t_vec *vec, t_shell *shell)
{
	if (contains_quote(arg) == S_QUOTE_CHAR)
	{
		if (new_strip_quotes(arg, vec, shell) == false)
			return (ft_vec_free(vec), FAILURE);
	}
	else if (contains_quote(arg) == D_QUOTE_CHAR)
	{
		if (will_expand(arg, shell, vec) == false)
			return (ft_vec_free(vec), FAILURE);
		// if (new_strip_quotes(arg, vec, shell) == false) // ! < echo "hello" incorrect strip (no expansion) if commented out
		// 	return (ft_vec_free(vec), FAILURE);
	}
	else
		if (will_expand(arg, shell, vec) == false)
			return (ft_vec_free(vec), FAILURE);
	return (SUCCESS);
}

static bool	process_args(t_cmd *cmd, t_shell *shell)
{
	int	i;
	t_vec	vec;

	i = 0;
	while (i < cmd->arg_count)
	{
		if (!cmd->args[i])
			return (SUCCESS);
		if (should_not_expand(cmd->args[i]) == true)
		{
			i++;
			continue ;
		}
		if (!ft_vec_init(&vec, 200))
			return (show_error_message(E_MALLOC, shell, "v fail", X_FAILURE), NULL);
		handle_args_expansion(cmd->args[i], &vec, shell);
		expand_arg(cmd, &vec, &i);
		i++;
	}
	return (SUCCESS);
}

static char	*process_cmd(char *cmd, t_shell *shell)
{
	t_vec	vec;
	char	*result;

	if (!cmd)
		return (NULL);
	if (should_not_expand(cmd) == true)
		return (cmd);
	if (!ft_vec_init(&vec, 200))
		return (show_error_message(E_MALLOC, shell, "v fail", X_FAILURE), NULL);
	if (contains_quote(cmd) == S_QUOTE_CHAR)
	{
		if (will_expand(cmd, shell, &vec) == false)
			return (ft_vec_free(&vec), cmd);
		if (new_strip_quotes(cmd, &vec, shell) == false)
			return (ft_vec_free(&vec), cmd);
	}
	else if (contains_quote(cmd) == D_QUOTE_CHAR)
	{
		if (will_expand(cmd, shell, &vec) == false)
			return (ft_vec_free(&vec), cmd);
		// if (new_strip_quotes(cmd, &vec, shell) == false) // ! < "echo" hello incorrect strip (no expansion) if commented out
		// 	return (ft_vec_free(&vec), cmd);
	}
	else
		return (ft_vec_free(&vec), cmd);
	result = (ft_vec_to_str(&vec));
	if (ft_strlen(result) == 0)
		return (ft_vec_free(&vec), cmd);
	return (result);
}

int	parser_post_process(t_shell *shell)
{
	int			i;
	// t_cmd		*cmd;
	char		*expanded_cmd;

	i = 0;
	// cmd = shell->cmd_table->cmds[i]; // ? does not work?
	expanded_cmd = NULL;
	while (i < shell->cmd_table->cmd_count)
	{
		expanded_cmd = process_cmd(shell->cmd_table->cmds[i]->value, shell);
		if (expanded_cmd && expanded_cmd != shell->cmd_table->cmds[i]->value)
		{
			free(shell->cmd_table->cmds[i]->value);
			shell->cmd_table->cmds[i]->value = expanded_cmd;
		}
		if (process_args(shell->cmd_table->cmds[i], shell) == false)
			return(show_error_message(E_MALLOC, shell, "vec args", X_FAILURE));
		i++;
	}
	return (0);
}
