/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/03 13:15:00 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/02/25 19:05:47 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ===== [ includes ] =====
# include "libft/includes/libft.h"
# include "error_messages.h"

// ===== [ libraries ] =====
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>


//===============================================================: Define
# define OPERATORS "<>|"
# define REDIRECTS "<>"

# define READ 0
# define WRITE 1

# define CYELLOW "\033[0;33m"
# define RESET_COLOR "\033[0m"

# define BUFF_SIZE 1024
# define PRINT_FLAG "-p"


//===============================================================: Enum
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
	REDIR_IN,
	REDIR_IN_APPEND,
	REDIR_OUT,
	END_OF_FILE,
	QUOTE,
	ARGFILE,
	NONE,
}	t_token_type;

typedef enum e_redirect_type
{
	IN,
	IN_APPEND,
	OUT,
	OUT_APPEND,
	END,
	REDIR_NONE,
}	t_redirect_type;

//===============================================================: Struct
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

typedef struct s_pipes
{
	int		prev_pipe[2];
	int		curr_pipe[2];
} t_pipes;

typedef struct s_redirect
{
	char				*value;
	int					fd;
	t_redirect_type		type;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmd
{
	t_redirect	*fd_in;
	t_redirect	*fd_out;
	t_redirect	*fd_err;
	t_redirect	*heredoc;
	char		*value;
	char		**args;
	char		**formatted_cmd;
	char		*cmd_path;
	int			arg_count;
}	t_cmd;

typedef struct s_cmd_table
{
	t_cmd		**cmds;
	int			cmd_count;
} t_cmd_table;

typedef struct	s_shell
{
	t_token				*tokens;
	t_cmd_table			*cmd_table;
	char				**envp;
	char const			*input;
	int					exit_code;
	int					single_quote;
	int					double_quote;
	bool				print_output;
}	t_shell;

typedef struct s_parse
{
	t_token		*tokens_r;
	t_token		*tokens_c;
	t_cmd		**cmds;
	int			current_pipe;
	int			cmd_count;
	int			i;
} t_parse;


//===============================================================: Main
// shell_init.c
t_shell	*shell_init(char **envp, char **argv);
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
bool			assign_redirect_types(t_token *tokens);
t_token_type	assign_type(char *value);

// post_lexer.c
bool	post_lexer(t_token *tokens);
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
char	**allocate_strings_split(t_split *sp);


//===============================================================: Parser
// parser.c
bool	parse(t_shell *shell);

// parser_checks.c
bool	parser_checks(t_token *tokens);

// parser_redirects.c
t_cmd	*construct_redirects(t_cmd *cmd, t_parse *p);

// parser_utils.c
t_parse		*init_parse(t_shell *shell);
t_cmd		*allocate_cmd(void);
t_token 	*locate_current_token(t_parse *p);
t_token		*locate_pipe_n(t_token *tokens_root, int pipe_count);


//===============================================================: Executor
// executor_enviroment.c
char	**format_cmd(t_cmd *cmd);
char	*get_path_for_cmd(char **env_paths, char *command);
char	**get_paths(void);

// executor_redirect.c
int		*fd_in_files(t_cmd *cmd);

// executor_utils.c
void	print_2d_char(char **arr);
int		prepare_command(t_shell *shell, int i);
int		new_process(t_shell *shell, int i, t_pipes *pipes);

// executor.c
int		execute(t_shell *shell);

// ----------------------------------- executor/command
// execute_commands.c
int		execute_command(t_shell *shell, int i);
int		execute_commands(t_shell *shell);

// redirect_command.c
void	open_redirects(t_cmd *cmd);

// single_command.c
int		single_command(t_shell *shell);
void	child_process(t_shell *shell);

// ----------------------------------- executor/pipe
// pipe_utils.c
t_pipes	*init_pipes(void);
void	will_open_pipe(t_cmd_table *cmd_table, t_pipes *pipes, int i);
void	will_close_pipes(t_pipes *pipes);
void	dup_fds(t_pipes *pipes, t_cmd *cmd);
void	iterate_pipes(t_pipes *pipes);

// ----------------------------------- executor/redirects
// redirect_heredoc
int		*collect_heredocs(t_cmd *cmd);

// redirect_in_files.c
int		*collect_fd_in_files(t_cmd *cmd);
void	redirect_in_files(t_cmd *cmd, int *fd_ins, int *fd_heredocs);

// redirect_open.c
void		open_in_redirects(t_cmd *cmd);

// redirect_types.c
t_redirect	*file_type(t_cmd *cmd, t_redirect_type type);
int			get_open_flag_for_type(t_redirect_type type);

// redirect_utils.c
int		count_redirects_for_type(t_cmd *cmd, t_redirect_type type);
size_t	read_large_file(int fd, char ***buff);


//===============================================================: Utils
// utils.c
void	print_token(t_token *tokens);

// clean_exit.c
int		count_pipes(t_shell *shell);
void	finish_lexer(t_shell *shell);
int		exit_with_message(t_error_messages error_code, t_message_colors color);

// print_cmds.c
void		print_cmds(t_cmd_table *cmd_table);
void 		should_print(char *s, bool should_print);

#endif
