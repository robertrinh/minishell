/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_tokens.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/22 15:12:33 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/05/29 16:22:41 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*type_to_string(t_token_type type)
{
	if (type == COMMAND)
		return ("command  ");
	if (type == ARGUMENT)
		return ("argument ");
	if (type == PIPE)
		return ("pipe     ");
	if (type == REDIRECT)
		return ("redirect ");
	if (type == REDIR_IN)
		return ("in       ");
	if (type == REDIR_IN_APPEND)
		return ("in_append");
	if (type == REDIR_OUT)
		return ("out      ");
	if (type == END_OF_FILE)
		return ("eof      ");
	if (type == S_QUOTE)
		return ("s_quote  ");
	if (type == D_QUOTE)
		return ("d_quote  ");
	if (type == ARGFILE)
		return ("argfile  ");
	if (type == NONE)
		return ("none     ");
	return (NULL);
}

t_validation	print_tokens(t_shell *shell)
{
	t_token		*tokens;

	if (shell->print_output == false)
		return (SUCCESS);
	ft_putstr_fd("\n\n========lexer========\n", STDOUT_FILENO);
	tokens = shell->tokens;
	while (tokens)
	{
		ft_putstr_fd(type_to_string(tokens->type), STDOUT_FILENO);
		ft_putstr_fd(" - \t ", STDOUT_FILENO);
		ft_putstr_fd(tokens->value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		tokens = tokens->next;
	}
	return (SUCCESS);
}

void	print_strings(char **strings)
{
	int		i;

	i = 0;
	while (strings[i])
	{
		ft_putstr_fd(strings[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
}
