/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_cmd_arguments.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/16 10:14:19 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/26 23:07:17 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft/lib_vector/vector.h"

static bool	is_type_arg(t_token_type type)
{
	if (type == ARGUMENT || type == S_QUOTE || type == D_QUOTE)
		return (true);
	return (false);
}

static int	count_args(t_parse *p)
{
	int			count;
	t_token		*current_token;

	count = 0;
	current_token = p->tokens_c;
	while (current_token)
	{
		if (current_token->type == PIPE)
			return (count);
		if (is_type_arg(current_token->type))
			count++;
		current_token = current_token->next;
	}
	return (count);
}

static char	**allocate_args(t_parse *p, t_shell *shell)
{
	char	**args;
	int		arg_count;
	int		i;

	i = 0;
	arg_count = count_args(p);
	args = safe_malloc(sizeof(char *) * (arg_count + 1), shell);
	while (i <= arg_count)
	{
		args[i] = NULL;
		i++;
	}
	return (args);
}

t_cmd	*construct_args(t_cmd *cmd, t_parse *p, t_shell *shell)
{
	int			i;
	t_token		*current;

	i = 0;
	current = p->tokens_c;
	cmd->args = allocate_args(p, shell);
	if (cmd->args == NULL)
		return (NULL);
	while (current)
	{
		if (is_type_arg(current->type))
		{
			cmd->args[i] = safe_strdup(current->value, shell);
			if (cmd->args[i] == NULL)
			{
				while (i > 0)
					free(cmd->args[--i]);
				return (free(cmd->args), NULL);
			}
			i++;
		}
		if (current->type == PIPE)
			break ;
		current = current->next;
	}
	cmd->arg_count = i;
	return (cmd);
}
