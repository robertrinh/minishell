/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_post_process.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/16 10:13:21 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/07/19 18:30:30 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*process_args(char **env, char *arg, t_shell *shell)
{
	t_vec	vec;
	char	*result;

	if (!arg)
		return (NULL);
	if (!ft_vec_init(&vec, 200))
		return (show_error_message(E_MALLOC, shell, "v fail", X_FAILURE), NULL);
	if (contains_quote(arg) == S_QUOTE_CHAR)
	{
		if (new_strip_quotes(arg, &vec, shell) == false)
		return (arg);
	}
	else if (contains_quote(arg) == D_QUOTE_CHAR)
	{
		if (will_expand(env, arg, shell, &vec) == false)
			return (ft_vec_free(&vec), arg);
		if (new_strip_quotes(arg, &vec, shell) == false)
			return (ft_vec_free(&vec), arg);
	}
	else
	{
		if (will_expand(env, arg, shell, &vec) == false)
			return (ft_vec_free(&vec), arg);
	}
	result = (ft_vec_to_str(&vec));
	if (ft_strlen(result) == 0)
		return (ft_vec_free(&vec), arg);
	return (result);
}

static char	*process_cmd(char **env, char *cmd, t_shell *shell)
{
	t_vec	vec;
	char	*result;

	if (!cmd)
		return (NULL);
	if (!ft_vec_init(&vec, 200))
		return (show_error_message(E_MALLOC, shell, "v fail", X_FAILURE), NULL);
	if (contains_quote(cmd) == S_QUOTE_CHAR)
	{
		if (will_expand(env, cmd, shell, &vec) == false)
			return (cmd);
		if (new_strip_quotes(cmd, &vec, shell) == false)
			return (cmd);
	}
	else if (contains_quote(cmd) == D_QUOTE_CHAR)
	{
		if (will_expand(env, cmd, shell, &vec) == false)
			return (cmd);
		if (new_strip_quotes(cmd, &vec, shell) == false)
			return (cmd);
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
	int		i;
	t_cmd	*cmd;
	char	*expanded_cmd;
	char	*expanded_arg;

	i = 0;
	expanded_cmd = NULL;
	expanded_arg = NULL;
	cmd = shell->cmd_table->cmds[i];
	while (i < shell->cmd_table->cmd_count)
	{
		expanded_cmd = process_cmd(shell->envp, cmd->value, shell);
		if (expanded_cmd && expanded_cmd != cmd->value)
		{
			free(cmd->value);
			cmd->value = expanded_cmd;
		}
		expanded_arg = process_args(shell->envp, cmd->args[i], shell);
		if (expanded_arg && expanded_arg != cmd->args[i])
		{
			free(cmd->args[i]);
			cmd->args[i] = expanded_arg;
		}
		i++;
	}
	return (0);
}
