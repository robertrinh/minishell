/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/03 13:15:00 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2023/12/14 16:35:37 by qtrinh        ########   odam.nl         */
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


//====================================================================: Minishell
char	*read_command(void);
t_shell	*shell_init();


//====================================================================: Lexer
t_token	*init_tokens(void);
t_token	*tokenize_command(char *input, t_token *tokens_root);
t_token	*token_builder(char *split_input);

#endif