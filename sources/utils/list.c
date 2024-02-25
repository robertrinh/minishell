/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/22 15:12:33 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/02/25 19:08:54 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_token(t_token *tokens)
{
	printf("\n\n========lexer========\n");
	while (tokens)
	{
		printf("%s - \t %s \n", type_to_string(tokens->type), tokens->value);
		tokens = tokens->next;
	}
}

t_token	*lstlast(t_token *token)
{
	if (!token)
		return (0);
	while (token->next)
		token = token->next;
	return (token);
}

t_token	*lst_copy(t_token *tokens_input)
{
	t_token	*tokens_current;
	t_token	*tokens_copy;
	t_token	*tokens_head;
	t_token	*new_token;
	int		i;

	i = 0;
	tokens_current = tokens_input;
	tokens_copy = token_constructor(tokens_current->value, i);
	i++;
	tokens_head = tokens_copy;
	tokens_current = tokens_current->next;
	while (tokens_current)
	{
		new_token = token_constructor(tokens_current->value, i);
		i++;
		tokens_copy->next = new_token;
		tokens_copy = tokens_copy->next;
		tokens_current = tokens_current->next;
	}
	return (tokens_head);
}

t_token	*lst_rev(t_token *tokens_head)
{
	t_token	*tokens_current;
	t_token	*tokens_temp_1;
	t_token	*tokens_temp_2;

	if (tokens_head == NULL || tokens_head->next == NULL)
		return (tokens_head);
	// init
	tokens_current = tokens_head;
	tokens_temp_1 = tokens_head->next;
	tokens_temp_2 = tokens_temp_1->next;

	// Reverse pointer
	tokens_current->next = NULL;
	tokens_temp_1->next = tokens_current;

	while (tokens_temp_2)
	{
		// Move all three forward
		tokens_current = tokens_temp_1;
		tokens_temp_1 = tokens_temp_2;
		tokens_temp_2 = tokens_temp_2->next;
		// Reset next
		tokens_temp_1->next = tokens_current;
	}
	return (tokens_temp_1);
}
