/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 13:15:00 by quentinbeuk       #+#    #+#             */
/*   Updated: 2023/12/21 17:46:37 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ===== [ includes ] =====
# include "libft/include/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

// typedef enum redirect
// {
// 	input = "<"
// 	output = ">"
// 	append_output = ">>"
// 	delimiter = "<<"
// }

// typedef char Delimiter = ' '
// dont forget about this!

//====================================================================: Enum
typedef enum e_token_types
{
	INFILE,
	OUTFILE,
	COMMAND,
	PIPE,
	HEREDOC,
	ARGUMENT,
	PROGRAM,
} t_token_type;


//====================================================================: Struct
typedef struct s_token
{
	t_token_type	type;
	int				len;
	char			*value;
	struct s_token	*next;
} t_token;


typedef struct s_cmd
{
	int		fd_in;
	int		fd_out;
	char	*arg;
} t_cmd;


typedef struct s_shell 
{
	t_token		*tokens;
	t_cmd		*cmds;
	int			exit_code;
} t_shell;


// minishell.c
void	print_token(t_token *tokens);

// shell_init.c
t_shell	*shell_init();

//====================================================================: Lexer
// lexer.c
t_token	*token_constructor(char *split_input);
t_token	*tokens_builder_manager(char *command, t_shell *shell);

// quotes.c
t_token *quote_manager(t_token *tokens_head);


#endif