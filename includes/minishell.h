/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 13:15:00 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/01/06 13:33:53 by qbeukelm         ###   ########.fr       */
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
typedef struct s_split
{
	int			len;
	int			i;
	int			i_check;
	int			i_buff;
	int			i_str;
	int			count;
	char		buffer[1000];
	char const	*input;
	char		**strings;
} t_split;

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
	int		single_quote;
	int		double_quote;
} t_cmd;

typedef struct s_shell 
{
	t_token		*tokens;
	t_cmd		*cmd;
	char const	*input;
	int			exit_code;
} t_shell;


// minishell.c
void	print_token(t_token *tokens);

// shell_init.c
t_shell	*shell_init();
void	input_init(char *input, t_shell *shell);
t_split	*init_split(t_shell *shell, t_split *split);

// list.c
t_token	*lstlast(t_token *token);
t_token *lst_rev(t_token *tokens_head);
t_token	*lst_copy(t_token *tokens_head);

//====================================================================: Lexer
// lexer.c
t_token	*token_constructor(char *split_input);
t_token	*tokens_builder_manager(t_shell *shell);

// quotes.c
t_token *quote_manager(t_shell *shell);

// quote_matcher.c
bool	is_outer_quote_match(t_shell *shell);

// split.c
char	**split(t_shell *shell);

#endif