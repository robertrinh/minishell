/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/03 13:13:52 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/15 12:54:02 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_token(t_token *tokens_head)
{
	if (tokens_head == NULL)
		return (false);
	return (true);
}

t_token	*token_constructor(char *split_input, int i)
{
	t_token	*token;

	token = safe_malloc(sizeof(t_token));
	token->len = ft_strlen(split_input);
	token->value = split_input;
	token->type = assign_type(token->value);
	token->next = NULL;
	token->i = i;
	return (token);
}

static t_token	*tokenize_command(t_shell *shell, t_token *tokens_head)
{
	int		i;
	char	**split_input;
	t_token	*current;
	t_token	*new;

	i = 0;
	split_input = split(shell);
	current = NULL;
	while (split_input[i])
	{
		new = token_constructor(split_input[i], i);
		if (is_token(current) == false)
		{
			current = new;
			tokens_head = current;
		}
		else
		{
			current->next = new;
			current = current->next;
		}
		i++;
	}
	return (tokens_head);
}

int	tokens_builder_manager(t_shell *shell)
{
	t_token	*tokens_head;

	tokens_head = NULL;
	tokens_head = tokenize_command(shell, tokens_head);
	shell->tokens = tokens_head;
	post_lexer(shell->tokens);

	return (SUCCESS);
}

int	lexer_manager(t_shell *shell)
{
	if (validate_quotes(shell) == FAILURE)
		return (exit_with_message(ERROR_UNMATCHED_QUOTE, RED, 0));
	if (tokens_builder_manager(shell) == SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}
