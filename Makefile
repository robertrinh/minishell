# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: quentinbeukelman <quentinbeukelman@stud      +#+                      #
#                                                    +#+                       #
#    Created: 2023/12/03 13:06:57 by quentinbeuk   #+#    #+#                  #
#    Updated: 2023/12/03 13:21:51 by quentinbeuk   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# ===== Names =====
NAME = minishell.a
NAME_EXECUTABLE = minishell


# ===== Compile =====
CC = gcc
CFlags = -Wall -Wextra -Werror


# ===== Colors =====
BOLD	:= \033[1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
RESET	:= \033[0m


# ===== Sources =====
SOURCES = minishell.c

SOURCES_LEXER = lexer.c


# ===== Manage Directories =====
INC = inc
DIR_OBJ = obj

DIR_SOURCES = sources
DIR_SOURCES_LEXER = sources/lexer


# ===== Object Files =====
OBJ = $(addprefix $(DIR_OBJ)/, $(SOURCES:.c=.o)) \
	$(addprefix $(DIR_OBJ)/, $(SOURCES_LEXER:.c=.o))


# ===== Rules =====
all: $(NAME_EXECUTABLE)

$(NAME_EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "$(GREEN)Successfully compiled $(NAME_EXECUTABLE)$(RESET)"

$(DIR_OBJ)/%.o: $(DIR_SOURCES)/%.c | $(DIR_OBJ)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(DIR_OBJ)/%.o: $(DIR_SOURCES_LEXER)/%.c | $(DIR_OBJ)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(DIR_OBJ):
	@mkdir -p $@


# ===== Clean =====
clean:
	@echo "$(BLUE)\nCleaning ...$(RESET)"
	@$(RM) -rf $(DIR_OBJ)
	@$(RM) -rf $(EXTRA_O)
	@$(RM) -rf $(OBJS)
	@$(RM) $(DIR_OBJ)/$(NAME)
	@echo "$(GREEN)$(BOLD)\nAll clean!\n$(RESET)"

fclean: clean
	@$(RM) $(NAME_EXECUTABLE)

re: fclean all

.PHONY: clean fclean re all
