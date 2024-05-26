/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/03 13:13:52 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/05/25 20:01:14 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*token_constructor(char *split_input, int i)
{
	t_token	*token;

	token = safe_malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->len = ft_strlen(split_input);
	token->value = ft_strdup(split_input);
	if (token->value == NULL)
	{
		show_error_message(E_MALLOC, C_RED, "safe_strdup()", X_FAILURE);
		return (NULL);
	}
	token->type = assign_type(token->value);
	token->next = NULL;
	token->i = i;
	return (token);
}

static t_token	*tokenize_command(t_token *tokens_head, t_shell *shell)
{
	int		i;
	t_split	*split_struct;
	t_token	*current;
	t_token	*new;

	i = 0;
	split_struct = split(shell);
	if (split_struct == NULL)
		return (NULL);
	current = NULL;
	new = NULL;
	while (split_struct->strings[i])
	{
		new = token_constructor(split_struct->strings[i], i);
		if (new == NULL)
		{
			free_split(split_struct);
			return (NULL);
		}
		if (current == NULL)
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
	free_split(split_struct);
	return (tokens_head);
}

int	tokens_builder_manager(t_shell *shell)
{
	t_token	*tokens_head;

	tokens_head = NULL;
	tokens_head = tokenize_command(tokens_head, shell);
	if (tokens_head == NULL)
		return (FAILURE);
	shell->tokens = tokens_head;
	post_lexer(shell->tokens);
	return (SUCCESS);
}

int	shell_lexer(t_shell *shell)
{
	if (validate_operators(shell->input) == FAILURE)
		return (show_error_message(E_OPERATOR, C_RED, "", X_FAILURE));
	if (validate_quotes(shell) == FAILURE)
		return (show_error_message(E_QUOTE, C_RED, "", X_FAILURE));
	if (tokens_builder_manager(shell) == SUCCESS)
		return (print_tokens(shell));
	return (FAILURE);
}
