# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 13:11:23 by wlin              #+#    #+#              #
#    Updated: 2024/07/22 14:09:32 by wlin             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

AUTHOR		= wlin, aglanuss
NAME			= minishell

CC				= gcc
CFLAGS		= -Wall -Wextra -Werror -g -Iincludes -I${LIBFT_DIR} -fsanitize=address -MMD
RM				= rm -fr

# *******************************	FILES	********************************** #

LIB         = lib/

LIBRARIES   = libft
LIBFT_DIR   = $(LIB)libft/
LIBRARY_PATHS = -L$(LIBFT_DIR)
LIBRARY_NAMES = -lft -lreadline
LDFLAGS     += $(LIBRARY_PATHS) $(LIBRARY_NAMES)

# HEADERS		= $(wildcard includes/*.h)
SRCS			= $(shell find src -name '*.c')
OBJS			= $(SRCS:.c=.o)
DEPS			= $(SRCS:.c=.d)
INCLUDES		= include

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
MAKE		=	make --no-print-directory

# ********************************	RULES	********************************** #

all:
	@$(MAKE) header
	@$(MAKE) $(NAME)

header:
	@printf "%b" "$(GREEN)"
	@echo "  __  __ _       _     _          _ _ "
	@echo " |  \/  (_)     (_)   | |        | | |"
	@echo " | \  / |_ _ __  _ ___| |__   ___| | |"
	@echo " | |\/| | | '_ \| / __| '_ \ / _ \ | |"
	@echo " | |  | | | | | | \__ \ | | |  __/ | |"
	@echo " |_|  |_|_|_| |_|_|___/_| |_|\___|_|_|"
	@echo
	@printf "%b" "$(BLUE)Name:	$(RED)$(NAME)\n"
	@printf "%b" "$(BLUE)Author:	$(RED)$(AUTHOR)\n"
	@printf "%b" "$(BLUE)CC: 	$(RED)$(CC)\n\033[m"
	@printf "%b" "$(BLUE)Flags: 	$(RED)$(CFLAGS)\n\033[m"
	@echo

libft:
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): libft $(OBJS)
	@echo "\n\n${BLUE_BOLD}[$(NAME)] $(GREEN)object files were created$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	echo "${BLUE_BOLD}[$(NAME)] $(GREEN)executable was created$(RESET)"

%.o: %.c Makefile
	@$(CC) $(CFLAGS) -DREADLINE_LIBRARY=1 $(RDFLAGS) -I $(INCLUDES) -I $(LIBFT_DIR) -c $< -o $@
	@echo "$(GREEN).$(RESET)\c"

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) $(OBJS)
	@echo "${BLUE_BOLD}[$(NAME)] $(RED)removed object files$(RESET)"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@echo "${BLUE_BOLD}[$(NAME)] $(RED)executable was deleted$(RESET)"

re: fclean
	@$(MAKE) all

-include $(DEPS)

.SILENT:

.PHONY: all clean fclean re libft