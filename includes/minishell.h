/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 13:15:00 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/09/02 14:00:39 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ===== [ includes ] =====
# include "libft/includes/libft.h"
# include "../includes/libft/lib_vector/vector.h"
# include "error_messages.h"
# include "builtins.h"

// ===== [ libraries ] =====
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

//===============================================================: Define
# define OPERATORS "<>|"
# define REDIRECTS "<>"
# define EXPAND_CHAR '$'
# define EXIT_CODE_CHAR '?'
# define EXPORT_DELIMITER '='
# define D_QUOTE_CHAR 34
# define S_QUOTE_CHAR 39
# define CMD_NOT_FOUND_STR "?"

# define READ 0
# define WRITE 1
# define C_YELLOW "\033[1;33m"
# define C_RED "\x1B[1;31m"
# define RESET_COLOR "\033[0m"

# define BUFF_SIZE 4096
# define PROCESS_SLEEP_TIME 5000
# define PRINT_FLAG "-p"

//===============================================================: Global
extern int	g_signal;

//===============================================================: Enum
typedef enum e_validation
{
	FAILURE,
	SUCCESS
}	t_validation;

typedef enum e_signal
{
	NO_SIG,
	PARENT,
	CHILD,
	HEREDOC
}	t_signal;

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
	S_QUOTE,
	D_QUOTE,
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

typedef enum e_main_builtin
{
	B_EXIT,
	B_CD,
	B_EXPORT,
	B_UNSET,
	B_NUM_MAIN
}	t_main_builtin;

typedef enum e_child_builtin
{
	B_ECHO,
	B_ENV,
	B_PWD,
	B_NUM_CHILD
}	t_child_builtin;

//===============================================================: Struct

typedef struct s_split
{
	int			len;
	int			i;
	int			i_check;
	int			i_buff;
	int			i_str;
	int			i_before;
	int			count;
	int			curr_export_arg;
	size_t		space_count;
	bool		is_export;
	char		*buffer;
	char		*input;
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

typedef struct s_childs
{
	int		child_count;
	pid_t	child_pid;
	int		pipe_fd[2][2];
}	t_childs;

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
	char		*value;
	char		**args;
	char		**cmd_and_args;
	char		*cmd_path;
	int			arg_count;
}	t_cmd;

typedef struct s_cmd_table
{
	t_cmd		**cmds;
	int			cmd_count;
}	t_cmd_table;

typedef struct s_shell
{
	t_split				*split;
	t_token				*tokens;
	t_cmd_table			*cmd_table;
	char				**envp;
	char				*input;
	int					single_quote;
	int					double_quote;
	bool				print_output;
	int					original_stdin;
	int					exit_code;
}	t_shell;

typedef struct s_parse
{
	t_token		*tokens_r;
	t_token		*tokens_c;
	t_cmd		**cmds;
	int			current_pipe;
	int			cmd_count;
	int			i;
}	t_parse;

typedef struct s_in_files
{
	int		*heredocs;
	int		*infiles;
}	t_in_files;

typedef struct s_cmd_data
{
	t_cmd		*cmd;
	t_shell		*shell;
	t_in_files	*ins;
}	t_cmd_data;

//===============================================================: Main
// shell_init.c
t_shell			*shell_pre_init(t_shell *shell, char **envp, char **argv);
bool			save_command(char *command, t_shell *shell);

//===============================================================: Lexer
// assign_type.c
bool			assign_redirect_types(t_token *tokens);
t_token_type	assign_type(char *value);

// lexer_utils.c
bool			is_special_type(t_token_type type);
t_token			*skip_operators(t_token *current);
t_token			*assign_argfile_args(t_token *current);
t_token			*assign_cmd_arg(t_token *current, int i);

// lexer.c
t_token			*token_constructor(char *split_input, int i, t_shell *shell);
int				tokens_builder_manager(t_shell *shell);
int				shell_lexer(t_shell *shell);

// post_lexer.c
bool			post_lexer(t_token *tokens);
bool			is_special_type(t_token_type type);

// validate_operators.c
t_validation	validate_operators(char *input);

//===============================================================: Lexer / Quote
// quotes.c
t_validation	validate_quotes(t_shell *shell);
int				contains_quote(const char *str);

// buffer_quote.c
int				is_quote(char c);
void			buffer_quote(t_split *sp, int quote_type);

//===============================================================: Lexer / Split
// allocate_strings.c
char			**allocate_strings_split(t_split *sp, t_shell *shell);

// split_handle_export_args_utils.c
void			did_add_spaces(size_t *i, size_t space_count, char *buffer);

// split_handle_export_args.c
bool			interpret_whitespace(t_split *sp);
bool			is_export(char *buffer);
bool			will_add_spaces(t_shell *shell, t_split *sp, \
	size_t space_count);
bool			has_multiple_export_delimiters(t_split *sp);
bool			should_handle_export(t_shell *shell, t_split *sp);

// split_utils.c
t_split			*init_split(t_shell *shell, t_split *split);
bool			is_white_space(char c);
int				skip_whitespace(t_split *sp);
int				check_operator(char c1, char c2);

// split.c
t_split			*split(t_shell *shell);

//===============================================================: Parser
// parser.c
bool			shell_parser(t_shell *shell);

// parser_cmd_arguments.c
t_cmd			*construct_args(t_cmd *cmd, t_parse *p, t_shell *shell);

// parser_post_process.c
int				parser_post_process(t_shell *shell);

// parser_checks.c
bool			parser_checks(t_shell *shell);

// parser_redirects_utils.c
t_redirect_type	assign_file_type(char *value);
bool			should_add_files(t_token_type current_type, t_token_type type);

// parser_redirects.c
t_cmd			*construct_redirects(t_cmd *cmd, t_parse *p, t_shell *shell);

// parser_strip_quotes.c
bool			new_strip_quotes(char *arg, t_vec *vec, t_shell *shell);
char			*strip_quote_for_type(char *arg);

// parser_utils.c
t_parse			*init_parse(t_shell *shell);
t_cmd			*allocate_cmd(t_shell *shell);
t_token			*locate_current_token(t_parse *p);
t_token			*locate_pipe_n(t_token *tokens_root, int pipe_count);

// ----------------------------------- parser/parser/patch
// parser_patch_cmd.c
bool			should_patch_command(t_shell *shell);

// parser_patch_export.c
bool			should_patch_export(t_shell *shell);

//===============================================================: Executor
// executor_enviroment.c
char			**format_cmd(t_cmd *cmd, t_shell *shell);
char			*get_path_for_cmd(char **env_paths, char *command);
char			*ft_getenv(t_shell *shell, char *input);
char			**get_paths(t_shell *shell);

// executor_redirect.c
int				*fd_in_files(t_cmd *cmd);

// executor_utils.c
bool			close_fds(int fd1, int fd2, int fd3);
int				prepare_command(t_shell *shell, int i);

// executor.c
int				shell_execute(t_shell *shell);

// ----------------------------------- executor/builtins

// builtins.c
bool			is_main_builtin(char *cmd_value);
bool			is_child_builtin(char *cmd_value);
int				exec_builtin(t_shell *shell, t_cmd *cmd);

// cd_utils.c
void			update_env(t_shell *shell);
void			cd_error(char *path, t_cmd *cmd, t_shell *shell);

// cd.c
int				cd(t_cmd *cmd, t_shell *shell);

// echo.c
int				echo(t_cmd *cmd, t_shell *shell);

// env.c
int				env(t_cmd *cmd, t_shell *shell);

// exit.c
int				exit_shell(t_cmd *cmd, t_shell *shell);

// export_utils.c
bool			is_valid_export_arg(const char *arg);

// export.c
int				export(t_cmd *cmd, t_shell *shell);

// pwd.c
int				pwd(t_cmd *cmd, t_shell *shell);

// unset.c
int				unset(t_cmd *cmd, t_shell *shell);

// ----------------------------------- executor/execute_command
// execute_commands.c
t_validation	execute_command(t_shell *shell, int i);
int				execute_commands(t_shell *shell);

// redirect_command.c
void			open_redirects(t_cmd *cmd);

// single_command.c
int				single_command(t_shell *shell);
t_validation	child_process(t_shell *shell);

// ----------------------------------- executor/execute_commands
// execute_commands.c
int				execute_commands(t_shell *shell);

// execute_pipe.c
void			first_cmd(t_shell *shell, t_cmd *cmd, \
					int pipe_out[2]);
void			mid_cmd(t_shell *shell, t_cmd *cmd, \
					int pipe_in, int pipe_out[2]);
int				final_cmd(t_shell *shell, t_cmd *cmd, int pipe_in);

// execute_piped_command.c
t_validation	execute_piped_command(t_shell *shell, t_cmd *cmd);

// execute_wait.c
int				wait_for_last_cmd(int child_count, int last_pid, \
					t_shell *shell);

// ----------------------------------- executor/pipe
// pipe_utils.c
int				count_pipes(t_shell *shell);

// ----------------------------------- executor/redirects
// redirect_heredoc
int				setup_heredoc(t_redirect *heredoc, int *stat_loc, \
					t_shell *shell);

// redirect_in_files.c
t_validation	redirect_in_files(t_cmd *cmd, int *stat_loc, t_shell *shell);

// redirect_open.c
int				safe_open(char *path, t_redirect_type oflag, int mode, \
					t_shell *shell);
t_in_files		*open_in_files(t_cmd_data *d, t_redirect_type type, \
					int *stat_loc);

// redirect_out_files.c
t_validation	redirect_out(t_cmd *cmd, t_shell *shell);

// redirect_types.c
t_redirect		*file_type(t_cmd *cmd, t_redirect_type type);
int				get_open_flag(t_redirect_type type);

// redirect_utils.c
void			free_ins(t_in_files *ins);
t_redirect_type	last_infile_type(t_cmd *cmd);
int				count_files(t_cmd *cmd, t_redirect_type type);

// ----------------------------------- executor/signals
// signals.c
void			handle_signals(t_signal signal_process);
void			rl_replace_line(const char *text, int clear_undo);

//===============================================================: Expander
// expander_utils.c
void			skip_multiple_expand_chars(char *arg, size_t *i);
int				count_expand(char *arg);
bool			check_expand_char(char *arg);
bool			expand_exit_code(t_vec *vec, t_shell *shell);

// expander.c
bool			will_expand(char *arg, t_shell *shell, t_vec *vec);

// get_env_key.c
char			*get_env_key(char *arg, size_t i, t_shell *shell);

//===============================================================: Utils
// control_utils.c
void			ft_sleep(size_t count);

// env_utils.c
char			*get_value_for_key(char **env, char *key, t_shell *shell);
int				count_lines_from(char **env, int index);
size_t			env_size(char **env);
int				index_for_env_key(char **input_env, char *key);

// function_protection.c
void			*safe_strjoin(const char *s1, const char *s2, t_shell *shell);
void			*safe_malloc(size_t size, t_shell *shell);
void			*safe_calloc(size_t count, size_t size, t_shell *shell);
char			*safe_strdup(char *str, t_shell *shell);
char			*safe_strdup_from(const char *str, int i, t_shell *shell);

// print_cmds.c
void			print_cmds(t_cmd_table *cmd_table);
void			should_print(char *s, bool should_print);

// print_tokens.c
t_validation	print_tokens(t_shell *shell);
void			print_strings(char **strings);

// shell_finish_cmd.c
void			free_cmd(t_cmd *cmd);

// shell_finish_utils.c
void			free_2d_array(char **array);
void			free_tokens(t_token *token);
void			free_cmd(t_cmd *cmd);
void			free_split(t_split *split);

// shell_finish.c
void			free_shell(t_shell *shell, bool will_exit);
void			shell_finish(t_shell *shell);

#endif
