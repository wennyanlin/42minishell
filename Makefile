# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aglanuss <aglanuss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 13:11:23 by wlin              #+#    #+#              #
#    Updated: 2024/06/06 09:42:35 by aglanuss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

AUTHOR		= wlin, aglanuss
NAME			= minishell

CC				= gcc
CFLAGS		= -Wall -Wextra -Werror -g -Iincludes -fsanitize=address
LDFLAGS		= -Llib -llibft
RM				= rm -fr

# *******************************	FILES	********************************** #

LIB         = lib/

LIBRARIES   = libft
LIBFT_DIR   = $(LIB)libft/
LIBRARY_PATHS = -L$(LIBFT_DIR)
LIBRARY_NAMES = -lft
LDFLAGS     += $(LIBRARY_PATHS) $(LIBRARY_NAMES)

HEADERS		= $(wildcard includes/*.h)
SRCS			= $(shell find src -name '*.c')
OBJS			= $(SRCS:.c=.o)

# *******************************  COLORS	******************************* #

RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW		=	\033[0;33m
BLUE			=	\033[0;34m
PURPLE		=	\033[0;35m
CYAN			=	\033[0;36m
RESET			=	\033[0m
GREEN_BOLD	=	\033[1;32m
BLUE_BOLD	=	\033[1;34m
CYAN_BOLD	=	\033[1;36m

# ********************************	RULES	********************************** #

all: $(NAME)

libft:
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(NAME): libft $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	@echo "${BLUE_BOLD}[$(NAME)] $(GREEN)executable was created$(RESET)"

%.o: %.c Makefile $(HEADERS)
	@$(CC) $(CFLAGS) -DREADLINE_LIBRARY=1 $(RDFLAGS) -c $< -o $@
	@echo "${YELLOW}Object compiling ${RESET}$@...${RESET}"

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(RM) $(OBJS)
	@echo "${BLUE_BOLD}[$(NAME)] $(RED)removed object files$(RESET)"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(RM) $(NAME)
	@echo "${BLUE_BOLD}[$(NAME)] $(RED)executable was deleted$(RESET)"

re: fclean
	@$(MAKE) all

.PHONY: all clean fclean re libft