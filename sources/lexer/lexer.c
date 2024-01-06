/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 13:13:52 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/01/06 14:14:19 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_token(t_token *tokens_head)
{
	if (tokens_head == NULL)
		return(false);
	return (true);
}

t_token	*token_constructor(char *split_input)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		// TODO Free
	token->len = ft_strlen(split_input);
	token->value = split_input;
	token->next = NULL;
	return (token);
}


static t_token	*tokenize_command(t_shell *shell, t_token *tokens_head)
{
	int	i;
	char **split_input;
	t_token	*current;
	t_token	*new;

	printf("\n\n========tokenizer========\n");
	i = 0;
	split_input = split(shell);
	current = NULL;
	while (split_input[i])
	{
		new = token_constructor(split_input[i]);
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

t_token	*tokens_builder_manager(t_shell *shell)
{
	t_token *tokens_head;

	tokens_head = NULL;
	tokens_head = tokenize_command(shell, tokens_head);
	shell->tokens = tokens_head;
	tokens_head = quote_manager(shell);
	return (tokens_head);
}
