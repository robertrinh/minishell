/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/03 13:15:00 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2023/12/08 18:00:58 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ===== [ includes ] =====
# include "libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

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

//====================================================================: Lexer
// ===== [ lexer.c ] =====
void	ft_print_lexer(char *str);

#endif