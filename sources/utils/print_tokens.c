/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:12:33 by qbeukelm          #+#    #+#             */
/*   Updated: 2024/02/29 13:24:38 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_tokens(t_token *tokens)
{
	printf("\n\n========lexer========\n");
	while (tokens)
	{
		printf("%s - \t %s \n", type_to_string(tokens->type), tokens->value);
		tokens = tokens->next;
	}
}
