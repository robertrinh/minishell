/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/03 13:13:49 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2023/12/08 17:59:33 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*read_command(void)
{
	char *input;

	input = readline("[minishell]: ");
	if (input == NULL)
	{
		// Free
	}
	return (input);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	while (1)
	{
		input = read_command();
		ft_printf("%s\n", input);
	}
	return (0);
}
