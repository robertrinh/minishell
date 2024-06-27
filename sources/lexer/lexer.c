/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/03 13:13:52 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/27 13:11:33 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*token_constructor(char *split_input, int i, t_shell *shell)
{
	t_token	*token;

	token = safe_malloc(sizeof(t_token), shell);
	if (token == NULL)
		return (NULL);
	token->len = ft_strlen(split_input);
	token->value = split_input;
	if (token->value == NULL)
	{
		show_error_message(E_MALLOC, shell, "safe_strdup token", X_FAILURE);
		return (NULL);
	}
	token->type = assign_type(token->value);
	token->next = NULL;
	token->i = i;
	return (token);
}

static void	assign_token(t_token **head, t_token **current, t_token *new)
{
	if (*current == NULL)
	{
		*current = new;
		*head = new;
	}
	else
	{
		(*current)->next = new;
		*current = new;
	}
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
		new = token_constructor(split_struct->strings[i], i, shell);
		if (new == NULL)
			return (free_split(split_struct), NULL);
		assign_token(&tokens_head, &current, new);
		i++;
	}
	shell->split = split_struct;
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
		return (show_error_message(E_OPERATOR, shell, "", X_FAILURE));
	if (validate_quotes(shell) == FAILURE)
		return (show_error_message(E_QUOTE, shell, "", X_FAILURE));
	if (tokens_builder_manager(shell) == SUCCESS)
		return (print_tokens(shell));
	return (FAILURE);
}
