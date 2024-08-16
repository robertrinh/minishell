/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_post_process.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/16 10:13:21 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/08/16 16:30:28 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	handle_expansion(char *str, t_vec *vec, t_shell *shell)
{
	if (contains_quote(str) == S_QUOTE_CHAR)
	{
		if (new_strip_quotes(str, vec, shell) == false)
			return (FAILURE);
	}
	else if (contains_quote(str) == D_QUOTE_CHAR)
	{
		if (will_expand(str, shell, vec) == false)
			return (FAILURE);
	}
	else
		if (will_expand(str, shell, vec) == false)
			return (FAILURE);
	return (SUCCESS);
}

static bool	process_expander(char **str, t_shell *shell)
{
	t_vec	vec;
	char	*expanded_str;

	expanded_str = NULL;
	if (!ft_vec_init(&vec, 200))
		return (show_error(E_MALLOC, shell, "", X_FAILURE), FAILURE);
	if (handle_expansion(*str, &vec, shell) == FAILURE)
		return (ft_vec_free(&vec), FAILURE);
	expanded_str = ft_vec_to_str(&vec);
	if (expanded_str != *str)
	{
		free(*str);
		*str = expanded_str;
	}
	return (SUCCESS);
}

static bool	process_args(t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 0;
	while (i < cmd->arg_count)
	{
		if (!cmd->args[i])
			return (SUCCESS);
		if (check_expand_char(cmd->args[i]) == false)
		{
			i++;
			continue ;
		}
		if (process_expander(&cmd->args[i], shell) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static bool	process_cmd(char **cmd, t_shell *shell)
{
	if (!*cmd)
		return (SUCCESS);
	if (check_expand_char(*cmd) == false)
		return (SUCCESS);
	if (process_expander(cmd, shell) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	parser_post_process(t_shell *shell)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = shell->cmd_table->cmds[i];
	while (i < shell->cmd_table->cmd_count)
	{
		if (process_cmd(&cmd->value, shell) == FAILURE)
			return (show_error(E_MALLOC, shell, "vec cmd", X_FAILURE));
		if (process_args(cmd, shell) == FAILURE)
			return (show_error(E_MALLOC, shell, "vec args", X_FAILURE));
		i++;
	}
	should_patch_command(shell);
	return (0);
}
