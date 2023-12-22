# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/03 13:06:57 by quentinbeuk       #+#    #+#              #
#    Updated: 2023/12/22 15:13:01 by qbeukelm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ===== Names =====
NAME_EXECUTABLE 	= minishell
LIBFT				= includes/libft


# ===== Compile =====
CC 					= cc
CFLAGS 				= -Wall -Wextra -Werror
HEADERS				= -I include -I ~/.brew/opt/readline/include -lreadline


# ===== Colors =====
BOLD				:= \033[1m
RED					:= \033[31;1m
GREEN				:= \033[32;1m
YELLOW				:= \033[33;1m
BLUE				:= \033[34;1m
RESET				:= \033[0m


# ===== Sources =====
SOURCES 			= minishell.c \
						shell_init.c \
						list.c 

SOURCES_LEXER 		= lexer.c \
						quote.c \
						quote_matcher.c 


# ===== Manage Directories =====
INC 				= inc
DIR_OBJ				= obj

DIR_SOURCES 		= sources
DIR_SOURCES_LEXER	= sources/lexer


# ===== Object Files =====
OBJ = $(addprefix $(DIR_OBJ)/, $(SOURCES:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_LEXER:.c=.o))


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
