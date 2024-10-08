# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/03 13:06:57 by quentinbeuk       #+#    #+#              #
#    Updated: 2024/09/02 13:57:54 by qbeukelm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ===== Colors =====
BOLD				:= \033[1m
RED					:= \033[31;1m
GREEN				:= \033[32;1m
YELLOW				:= \033[33;1m
BLUE				:= \033[34;1m
RESET				:= \033[0m


# ===== Sources =====
SOURCES 				= minishell.c \

SOURCES_LEXER 			= assign_type.c \
							lexer.c \
							post_lexer_utils.c \
							post_lexer.c \
							validate_operators.c

SOURCES_LEXER_SPLIT	 	= allocate_strings.c \
							split_handle_export_args_utils.c \
							split_handle_export_args.c \
							split_utils.c \
							split.c

SOURCES_LEXER_QUOTE		= quote.c \
							buffer_quote.c

SOURCES_PARSER			=  parser_checks.c \
							parser_cmd_arguments.c \
							parser_post_process.c \
							parser_redirects_utils.c \
							parser_redirects.c \
							parser_strip_quotes.c \
							parser_utils.c \
							parser.c

SOURCES_PARSER_PATCH	= parser_patch_cmd.c \
							parser_patch_export.c

SOURCES_UTILS			= control_utils.c \
							env_utils.c \
							error_messages.c \
							function_protection.c \
							print_cmds.c \
							print_tokens.c \
							shell_finish_cmd.c \
							shell_finish_utils.c \
							shell_finish.c \
							shell_init.c

SOURCES_EXECUTOR		= executor_environment.c \
							executor_utils.c \
							executor.c

SOURCES_BUILTINS		= builtins.c \
								cd.c \
								cd_utils.c \
								echo.c \
								env.c \
								exit.c \
								export_utils.c \
								export.c \
								pwd.c \
								unset.c

SOURCES_EXECUTOR_COMMAND	= execute_command.c \
								single_command.c

SOURCES_EXECUTOR_COMMANDS = execute_commands.c \
								execute_pipe.c \
								execute_piped_command.c \
								execute_wait.c
							
SOURCES_EXECUTOR_PIPE	= pipe_utils.c

SOURCES_EXECUTOR_REDIRECTS	= redirect_heredoc.c \
								redirect_in_files.c \
								redirect_open.c \
								redirect_out_files.c \
								redirect_types.c \
								redirect_utils.c

SOURCES_EXECUTOR_SIGNALS	= signals.c

SOURCES_EXPANDER		= expander_utils.c \
								expander.c \
								get_env_key.c


# ===== Manage Directories =====
INC 					= inc
DIR_OBJ					= obj

DIR_SOURCES 			= sources
DIR_SOURCES_LEXER		= sources/lexer
DIR_SOURCES_LEXER_SPLIT = sources/lexer/split
DIR_SOURCES_LEXER_QUOTE = sources/lexer/quote
DIR_SOURCES_PARSER		= sources/parser
DIR_SOURCES_PARSER_PATCH	= sources/parser/parser_patch
DIR_SOURCES_UTILS		= sources/utils
DIR_SOURCES_EXECUTOR	= sources/executor
DIR_SOURCES_BUILTINS	= sources/builtins
DIR_SOURCES_EXECUTOR_COMMAND = sources/executor/execute_command
DIR_SOURCES_EXECUTOR_COMMANDS = sources/executor/execute_commands
DIR_SOURCES_EXECUTOR_PIPE = sources/executor/pipe
DIR_SOURCES_EXECUTOR_REDIRECTS = sources/executor/redirects
DIR_SOURCES_EXECUTOR_SIGNALS = sources/executor/signals
DIR_SOURCES_EXPANDER 	= sources/expander


# ===== Object Files =====
OBJ = $(addprefix $(DIR_OBJ)/, $(SOURCES:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_LEXER:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_LEXER_SPLIT:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_LEXER_QUOTE:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_PARSER:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_PARSER_PATCH:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_UTILS:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_EXECUTOR:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_BUILTINS:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_EXECUTOR_COMMAND:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_EXECUTOR_COMMANDS:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_EXECUTOR_PIPE:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_EXECUTOR_REDIRECTS:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_EXECUTOR_SIGNALS:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_EXECUTOR_SIGNALS:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_EXPANDER:.c=.o))

# ===== Names =====
NAME_EXECUTABLE 	= minishell
LIBFT				= includes/libft

# ===== Compile =====
CC 					= cc
CFLAGS 				= #-Wall -Werror -Wextra -g #-fsanitize=address

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	READLINE_LOC = /usr/lib/aarch64-linux-gnu/libreadline.so
	READLINE_LIB = -L $(READLINE_LOC) -lreadline
endif
ifeq ($(UNAME_S),Darwin)
	READLINE_LOC = ~/.brew/opt/readline
	READLINE_LIB = -L $(READLINE_LOC)/lib -lreadline
endif

READLINE_INCLUDE	=	-I includes -I $(READLINE_LOC)/include


# ===== Rules =====
all: $(NAME_EXECUTABLE)

$(NAME_EXECUTABLE): $(OBJ)
	@echo "$(BLUE)\nMaking LIBFT ...\n$(RESET)"
	@$(MAKE) -C $(LIBFT) >/dev/null
	@echo "$(BLUE)Making MINISHELL ...\n$(RESET)"
	@$(CC) $(CFLAGS) $^ $(READLINE_LIB) $(LIBFT)/libft.a -o $(NAME_EXECUTABLE)
	@echo "$(GREEN)Compiled all!\n$(RESET)"

$(DIR_OBJ)/%.o: $(DIR_SOURCES)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(DIR_OBJ)/%.o: $(DIR_SOURCES_LEXER)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(DIR_OBJ)/%.o: $(DIR_SOURCES_LEXER_SPLIT)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(DIR_OBJ)/%.o: $(DIR_SOURCES_LEXER_QUOTE)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(DIR_OBJ)/%.o: $(DIR_SOURCES_PARSER)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(DIR_OBJ)/%.o: $(DIR_SOURCES_PARSER_PATCH)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(DIR_OBJ)/%.o: $(DIR_SOURCES_UTILS)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(DIR_OBJ)/%.o: $(DIR_SOURCES_EXECUTOR)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(DIR_OBJ)/%.o: $(DIR_SOURCES_BUILTINS)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(DIR_OBJ)/%.o: $(DIR_SOURCES_EXECUTOR_COMMAND)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(DIR_OBJ)/%.o: $(DIR_SOURCES_EXECUTOR_COMMANDS)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(DIR_OBJ)/%.o: $(DIR_SOURCES_EXECUTOR_PIPE)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(DIR_OBJ)/%.o: $(DIR_SOURCES_EXECUTOR_REDIRECTS)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(DIR_OBJ)/%.o: $(DIR_SOURCES_EXECUTOR_SIGNALS)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(DIR_OBJ)/%.o: $(DIR_SOURCES_EXPANDER)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(DIR_OBJ):
	@mkdir -p $@


# ===== Valgrind =====
valgrind:
	valgrind --leak-check=full --track-origins=yes  ./minishell


# ===== Clean =====
clean:
	@echo "$(BLUE)\nCleaning ...$(RESET)"
	@$(MAKE) clean -C ./includes/libft/ >/dev/null
	@$(RM) -rf $(DIR_OBJ)
	@$(RM) -rf $(EXTRA_O)
	@$(RM) -rf $(OBJS)
	@echo "$(GREEN)$(BOLD)\nAll clean!\n$(RESET)"

fclean: clean
	@$(MAKE) fclean -C ./includes/libft/ >/dev/null
	@$(RM) $(NAME_EXECUTABLE)

re: fclean all

.PHONY: clean fclean re all
