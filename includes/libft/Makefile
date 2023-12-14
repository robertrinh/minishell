# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: qtrinh <qtrinh@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/04 17:09:25 by qtrinh        #+#    #+#                  #
#    Updated: 2023/10/26 17:19:41 by qtrinh        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re
NAME := libft.a

CC := gcc
CFLAGS := -Wall -Wextra -Werror
AR := ar rcs
INCLUDE := -I ./include

SRC_CHARACTER = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_tolower.c ft_toupper.c
SRC_LIST = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
SRC_MEMORY = ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_free_2d.c
SRC_WRITE = ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
SRC_STRING = ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_strmapi.c ft_striteri.c ft_atoi.c ft_ayetoi.c ft_itoa.c ft_split.c ft_atod.c
SRC_GET_NEXT_LINE = get_next_line.c get_next_line_utils.c
SRC_FT_PRINTF = ft_printf.c ft_printf_hex.c ft_printf_pointer.c ft_printf_stuff.c ft_printf_unsigned.c

SRC += $(SRC_CHARACTER) $(SRC_LIST) $(SRC_MEMORY) $(SRC_WRITE) $(SRC_STRING) $(SRC_GET_NEXT_LINE) $(SRC_FT_PRINTF)
vpath %.c character get_next_line include linked_list memory string write ft_printf
OBJ = $(patsubst %.c, $(OBJDIR)/%.o, $(SRC))

OBJDIR = objects

#COLORS SHOW
BOLD_GREEN=\033[1;92m
BOLD_RED=\033[1;91m
RED=\033[0;31m
PURPLE=\033[0;35m
YELLOW=\033[0;33m
GRAY=\033[0;37m
INTENSE_CYAN=\033[0;96m
END_COLOUR=\033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "    __    ________  ____________                       __      __"
	@echo "   / /   /  _/ __ )/ ____/_  __/  ________  ____ _____/ /_  __/ /"
	@echo "  / /    / // __  / /_    / /    / ___/ _ \/ __  / __  / / / / / "
	@echo " / /____/ // /_/ / __/   / /    / /  /  __/ /_/ / /_/ / /_/ /_/  "
	@echo "/_____/___/_____/_/     /_/    /_/   \___/\__,_/\__,_/\__, (_)   "
	@echo "                                                     /____/      "

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c 
	@mkdir -p $(OBJDIR)
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@echo "${BOLD_RED}THANOS SNAPPED! ${GRAY}Spider senses tingling...$(END_COLOUR)"

fclean: clean
	@rm -f $(NAME)
	@echo "${RED}Mister stark, I don't feel so good.. $(INTENSE_CYAN)LIBFT DISSOLVED 🥺 $(END_COLOUR)"

re: fclean all
