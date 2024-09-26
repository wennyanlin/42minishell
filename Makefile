# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 13:11:23 by wlin              #+#    #+#              #
#    Updated: 2024/09/24 13:10:22 by wlin             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

AUTHORS			= wlin rtorrent
NAME			= minishell

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -g -Iincludes -I${LIBFT_DIR} -fsanitize=address -MMD
RM				= rm -fr
MAKE			= make

#<--------------------------------->FILES<------------------------------------>#

LIBRARIES		= libft
LIBFT_DIR		= lib/libft/
LIBRARY_PATHS	= -L$(LIBFT_DIR)
LIBRARY_NAMES	= -lft -lreadline
LDFLAGS			+= $(LIBRARY_PATHS) $(LIBRARY_NAMES)

HEADERS			= includes/minishell.h
FILES_MAIN		= main.c
FILES_LEXR		= lexer.c utils_list.c utils_str.c
FILES_PARS		= parser.c parser_syntax.c parser_utils.c
FILES_EXEC		= executor.c exec_find_cmd.c here_doc.c process_init.c\
				  process.c exec_utils.c  split_path.c shell_expansion.c
FILES_BLT		= builtin.c env.c exit.c pwd.c unset.c
FILES_AUX		= aux_array.c aux_str.c
FILES_TEST		= test_lexer.c

DIR_SRC			= src/
DIR_OBJ_DEPS	= obj_deps/

INCLUDES		= include/

DIR_LEXR_TEST	= test/
DIR_LEXR		= lexer/
DIR_PARS		= parser/
DIR_EXEC		= executor/
DIR_AUX			= auxiliaries/
DIR_BLT			= builtin/

SRCS_MAIN		= $(FILES_MAIN)
SRCS_TEST		= $(addprefix $(DIR_LEXR_TEST),$(FILES_TEST))
SRCS_LEXR		= $(addprefix $(DIR_LEXR),$(FILES_LEXR))
SRCS_PARS		= $(addprefix $(DIR_PARS),$(FILES_PARS))
SRCS_EXEC		= $(addprefix $(DIR_EXEC),$(FILES_EXEC))
SRCS_AUX		= $(addprefix $(DIR_AUX),$(FILES_AUX))
SRCS_BLT		= $(addprefix $(DIR_BLT),$(FILES_BLT))

ALL_SRCS		:= $(SRCS_MAIN) $(SRCS_LEXR) $(SRCS_PARS) $(SRCS_EXEC)\
				   $(SRCS_AUX) $(SRCS_BLT) $(SRCS_TEST)
ALL_OBJS		:= $(addprefix $(DIR_OBJ_DEPS),$(ALL_SRCS:.c=.o))
ALL_DEPS		:= $(ALL_OBJS:.o=.d)
ALL_SRCS		:= $(addprefix $(DIR_SRC),$(ALL_SRCS))

#<-------------------------------->COLORS<------------------------------------>#

RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW			=	\033[0;33m
BLUE			=	\033[0;34m
PURPLE			=	\033[0;35m
CYAN			=	\033[0;36m
RESET			=	\033[0m
GREEN_BOLD		=	\033[1;32m
BLUE_BOLD		=	\033[1;34m
CYAN_BOLD		=	\033[1;36m

#<--------------------------------->RULES<------------------------------------>#

all: header $(NAME)

header:
	@printf "%b" "$(GREEN)"
	@echo "  __  __ _       _     _          _ _ "
	@echo " |  \/  (_)     (_)   | |        | | |"
	@echo " | \  / |_ _ __  _ ___| |__   ___| | |"
	@echo " | |\/| | | '_ \| / __| '_ \ / _ \ | |"
	@echo " | |  | | | | | | \__ \ | | |  __/ | |"
	@echo " |_|  |_|_|_| |_|_|___/_| |_|\___|_|_|"
	@echo
	@printf "%b" "$(BLUE)Name:    $(RED)$(NAME)\n"
	@printf "%b" "$(BLUE)Authors: $(RED)$(AUTHORS)\n"
	@printf "%b" "$(BLUE)CC:      $(RED)$(CC)\n"
	@printf "%b" "$(BLUE)Flags:   $(RED)$(CFLAGS)$(RESET)\n"
	@echo

libft:
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory bonus
	@echo "\n${BLUE_BOLD}[libft] $(GREEN)object files were created$(RESET)"

$(NAME): libft $(ALL_OBJS)
	@echo "\n${BLUE_BOLD}[$(NAME)] $(GREEN)object files were created$(RESET)"
	@$(CC) $(CFLAGS) $(ALL_OBJS) -o $(NAME) $(LDFLAGS)
	@echo "\n${BLUE_BOLD}[$(NAME)] $(GREEN)executable was created$(RESET)"

obj_deps/%.o: src/%.c Makefile
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -DREADLINE_LIBRARY=1 $(RDFLAGS) -I $(INCLUDES) -I\
	$(LIBFT_DIR) -o $@ -c $<
	@echo "\n$(CC) $(CFLAGS) -DREADLINE_LIBRARY=1 $(RDFLAGS) -I $(INCLUDES)\
	-I $(LIBFT_DIR) -o $@ -c $<\c"
	@echo "$(GREEN)$(RESET)\c"

clean:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@echo "${BLUE_BOLD}[$(NAME)] ${RED}Removing object and dependecy files...\
	${RESET}"
	$(RM) $(ALL_OBJS) $(ALL_DEPS)
	@echo "${BLUE_BOLD}[$(NAME)] ${GREEN}Object and dependecy files removed\
	from $(DIR_OBJ_DEPS), $(LIBFT_DIR)\n"

fclean: clean
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "${BLUE_BOLD}[$(NAME)] ${RED}Removing executable...${RESET}"
	$(RM) $(NAME)
	@$(RM) $(DIR_OBJ_DEPS)
	@echo "${BLUE_BOLD}[$(NAME)] ${GREEN}Executable deleted${RESET}"

re: fclean all

-include $(ALL_DEPS)

# .SILENT:

.PHONY: all clean fclean re libft header
