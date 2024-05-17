/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/03 13:13:52 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/05/10 17:44:56 by qtrinh        ########   odam.nl         */
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
	token->value = safe_strdup(split_input);
	token->type = assign_type(token->value);
	token->next = NULL;
	token->i = i;
	return (token);
}

static t_token	*tokenize_command(t_token *tokens_head, t_split *sp)
{
	int		i;
	char	**split_input;
	t_token	*current;
	t_token	*new;

	i = 0;
	split_input = split(sp);
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
	free_split(sp);
	return (tokens_head);
}

int	tokens_builder_manager(t_shell *shell)
{
	t_token	*tokens_head;
	t_split		*split;

	split = safe_malloc(sizeof(t_split));
	split = init_split(shell, split);
	tokens_head = NULL;
	tokens_head = tokenize_command(tokens_head, split);
	shell->tokens = tokens_head;
	post_lexer(shell->tokens);
	return (SUCCESS);
}

int	shell_lexer(t_shell *shell)
{
	if (validate_operators(shell->input) == FAILURE)
		return (show_error_message(E_OPERATOR, C_RED, "", X_OPERATOR));
	if (validate_quotes(shell) == FAILURE)
		return (show_error_message(E_QUOTE, C_RED, "", X_QUOTE));
	if (tokens_builder_manager(shell) == SUCCESS)
		return (print_tokens(shell));
	return (FAILURE);
}
