/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/03 13:15:00 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/01/26 21:15:00 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ===== [ includes ] =====
# include "libft/include/libft.h"
# include "error_messages.h"

// ===== [ libraries ] =====
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>


//====================================================================: Define
# define OPERATORS "<>|"
# define REDIRECTS "<>"

# define CYELLOW "\033[0;33m"
# define RESET_COLOR "\033[0m"


//====================================================================: Enum
typedef enum e_exit
{
	FAILURE,
	SUCCESS
}	t_exit;

typedef enum e_direction
{
	LEFT,
	RIGHT
}	t_direction;

typedef enum e_token_type
{
	COMMAND,
	ARGUMENT,
	PIPE,
	REDIRECT,
	HEREDOC,
	QUOTE,
	ARGFILE,
	NONE,
}	t_token_type;


//====================================================================: Struct
typedef struct s_ast_node
{
	t_token_type		type;
	char				*value;
	struct s_ast_node	**children;
	int					num_children;
	struct s_ast_node	*parent;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

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
}	t_split;

typedef struct s_token
{
	t_token_type	type;
	int				len;
	int				i;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_parse
{
	t_ast_node	*ast_r;
	t_ast_node	*ast_c;
	t_token		*tokens_c;
	t_token		*tokens_r;
}	t_parse;

typedef struct s_cmd
{
	int		fd_in;
	int		fd_out;
	int		fd_err;
	char	*arg;
	int		single_quote;
	int		double_quote;
}	t_cmd;

typedef struct s_shell
{
	t_token		*tokens;
	t_cmd		*cmd;
	char const	*input;
	int			exit_code;
}	t_shell;


//===============================================================: Main
// shell_init.c
t_shell	*shell_init(void);
bool	save_command(char *input, t_shell *shell);
t_split	*init_split(t_shell *shell, t_split *split);

// list.c
t_token	*lstlast(t_token *token);
t_token	*lst_rev(t_token *tokens_head);
t_token	*lst_copy(t_token *tokens_head);
void	print_token(t_token *tokens);


//===============================================================: Lexer
// lexer.c
char	*type_to_string(t_token_type type);
t_token	*token_constructor(char *split_input, int i);
int		tokens_builder_manager(t_shell *shell);
int		lexer_manager(t_shell *shell);

// assign_type.c
t_token_type	assign_type(char *value);

// post_lexer.c
bool	post_lexer(t_shell *shell);
bool	is_special_type(t_token_type type);


//===============================================================: Lexer / Quote
// quotes.c
int		is_quote(char c);
int		quote_manager(t_shell *shell);

// buffer_quote.c
void	buffer_quote(t_split *sp, int quote_type);


//===============================================================: Lexer / Split
// split.c
char	**split(t_shell *shell);
bool	is_white_space(char c);
int		skip_whitespace(t_split *sp);
int		check_operator(char c1, char c2);

// allocate_strings.c
char	**allocate_strings(t_split *sp);


//===============================================================: Parser
// lexer_to_parser_pipe.c
t_ast_node		*tokens_to_parser_pipe(t_token *tokens_root);

// lexer_to_parser.c
bool	make_command_node(t_parse *p);
bool	make_parent_node(t_parse *p);
bool	make_redirect_node(t_parse *p);
t_ast_node	*tokens_to_parser(t_token *tokens_root);

// parser_checks.c
int				check_pipes(t_token *tokens);

// parser_construct_command.c
bool		construct_command_node(t_parse *p, t_direction direction);
bool		construct_arg_nodes(t_parse *p, t_direction direction);

// parser_construct_pipes.c
t_token		*fill_start_location(t_token *tokens_root, t_token *current, int pipe_count);
bool		construct_pipe_node(t_parse *p, int pipe_count);

// parser_construct_redirects.c
t_token		*fill_start_location(t_token *tokens_root, t_token *current, int pipe_count);
bool 		construct_argfile_node(t_parse *p, t_token *current);
bool		construct_redirect_nodes(t_parse *p, int pipe_count);

// parser_operations.c
typedef void 	(*HANDLE_FUNCTIONS)(t_ast_node*);
extern 			HANDLE_FUNCTIONS handle_functions[];

// parser_pipe_utils.c
bool		contains_pipe(t_token *current);
t_token		*locate_pipe_n(t_token *tokens_root, int pipe_count);

// parser_utils.c
t_parse 		*init_parse(t_token *tokens_root);
t_ast_node		*ast_constructor(t_token *current, t_ast_node *parent);
int 			count_children(t_token *current_cmd);

// parser.c
int			parse_lexer(t_token *tokens_root);


//===============================================================: Utils
// utils.c
void	print_token(t_token *tokens);

// clean_exit.c
void	finish_command(t_shell *shell);
int		exit_with_message(t_error_messages error_code, t_message_colors color);

#endif
