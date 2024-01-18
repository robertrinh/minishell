# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: qbeukelm <qbeukelm@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2023/12/03 13:06:57 by quentinbeuk   #+#    #+#                  #
#    Updated: 2024/01/17 17:32:37 by quentinbeuk   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# ===== Names =====
NAME_EXECUTABLE 	= minishell
LIBFT				= includes/libft


# ===== Compile =====
CC 					= cc
CFLAGS 				= 
HEADERS				= -I include -I ~/.brew/opt/readline/include -lreadline


# ===== Colors =====
BOLD				:= \033[1m
RED					:= \033[31;1m
GREEN				:= \033[32;1m
YELLOW				:= \033[33;1m
BLUE				:= \033[34;1m
RESET				:= \033[0m


# ===== Sources =====
SOURCES 				= minishell.c \
							shell_init.c 

SOURCES_LEXER 			= lexer.c \
							assign_type.c \
							post_lexer.c

SOURCES_LEXER_SPLIT	 	= split.c \
							split_utils.c \
							allocate_strings.c \
							

SOURCES_LEXER_QUOTE		= quote.c \
							buffer_quote.c \

SOURCES_PARSER			= parser.c \
							parse_operations.c

SOURCES_UTILS			= clean_exit.c \
							list.c \
							error_messages.c


# ===== Manage Directories =====
INC 					= inc
DIR_OBJ					= obj

DIR_SOURCES 			= sources
DIR_SOURCES_LEXER		= sources/lexer
DIR_SOURCES_LEXER_SPLIT = sources/lexer/split
DIR_SOURCES_LEXER_QUOTE = sources/lexer/quote
DIR_SOURCES_PARSER		= sources/parser
DIR_SOURCES_UTILS		= sources/utils


# ===== Object Files =====
OBJ = $(addprefix $(DIR_OBJ)/, $(SOURCES:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_LEXER:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_LEXER_SPLIT:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_LEXER_QUOTE:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_PARSER:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_UTILS:.c=.o))


# ===== Rules =====
all: $(NAME_EXECUTABLE)

$(NAME_EXECUTABLE): $(OBJ)
	@echo "$(BLUE)\nMaking LIBFT ...\n$(RESET)"
	@$(MAKE) -C $(LIBFT)
	@echo "$(BLUE)\nMaking MINISHELL ...\n$(RESET)"
	@$(CC) $(CFLAGS) $(HEADERS) $^ $(LIBFT)/libft.a -o $(NAME_EXECUTABLE) 
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

$(DIR_OBJ)/%.o: $(DIR_SOURCES_UTILS)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(DIR_OBJ):
	@mkdir -p $@


# ===== Clean =====
clean:
	@echo "$(BLUE)\nCleaning ...$(RESET)"
	@$(MAKE) clean -C ./includes/libft/
	@$(RM) -rf $(DIR_OBJ)
	@$(RM) -rf $(EXTRA_O)
	@$(RM) -rf $(OBJS)
	@echo "$(GREEN)$(BOLD)\nAll clean!\n$(RESET)"

fclean: clean
	@$(MAKE) fclean -C ./includes/libft/
	@$(RM) $(NAME_EXECUTABLE)

re: fclean all

.PHONY: clean fclean re all
