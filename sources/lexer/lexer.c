/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/03 13:13:52 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2023/12/14 18:01:37 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_node(t_token *tokens_head)
{
	if (tokens_head == NULL)
		return(false);
	return (true);
}

t_token	*tokenize_command(char *input, t_token *tokens_head)
{
	int	i;
	char **split_input;
	t_token	*current;
	t_token	*new;

	printf("\n\n========tokenizer========\n");
	i = 0;
	split_input = ft_split(input, ' ');
	current = NULL;
	while (split_input[i])
	{
		new = token_builder(split_input[i]);
		if (is_node(current) == false)
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

t_token	*token_builder(char *split_input)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		//exit
	token->len = ft_strlen(split_input);
	token->value = split_input;
	token->next = NULL;

	printf("token_builder: %s\n", token->value);
	
	return (token);
}

