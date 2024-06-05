# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 13:11:23 by wlin              #+#    #+#              #
#    Updated: 2024/05/30 15:22:50 by wlin             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -g -fsanitize=address
RDFLAGS		:= -lreadline
HEADER		:= ./includes/minishell.h
INCLUDE		:= ./lib/libft.a

RM			:= rm -fr

DIR_OBJ		:=	obj/
DIR_SRC		:=	src/
DIR_RDL		:=	readline/
DIR_LIB		:=	lib/libft/
DIR_LXR		:=	lexer/
DIR_PARS	:=	parser/
DIR_BLT		:=	builtins/
DIR_EXP		:=	expansor/
DIR_EXEC	:=	executor/
DIR_PMT		:=	prompt/
DIR_HRD		:=	heredoc/

# *******************************	FILES	********************************** #

FILES		:=
FILES_LXR	:=
FILES_PRS	:=
FILES_BLT	:=
FILES_EXP	:=
FILES_EXEC	:=
FILES_PMT	:=
FILES_HRD	:=

SRC_FILES	:=	$(addprefix $(DIR_SRC),$(FILES))
SRC_LXR		:=	$(addprefix $(DIR_SRC),$(addprefix $(DIR_LXR),$(FILES_LXR)))
SRC_PRS		:=	$(addprefix $(DIR_PRS),$(addprefix $(DIR_PRS),$(FILES_PRS)))
SRC_BLT		:=	$(addprefix $(DIR_BLT),$(addprefix $(DIR_BLT),$(FILES_BLT)))
SRC_EXP		:=	$(addprefix $(DIR_EXP),$(addprefix $(DIR_EXP),$(FILES_EXP)))
SRC_EXEC	:=	$(addprefix $(DIR_EXEC),$(addprefix $(DIR_EXEC),$(FILES_EXEC)))
SRC_PMT		:=	$(addprefix $(DIR_PMT),$(addprefix $(DIR_PMT),$(FILES_PMT)))
SRC_HRD		:=	$(addprefix $(DIR_HRD),$(addprefix $(DIR_HRD),$(FILES_HRD)))

# *******************************	OBJECTS	********************************** #

OBJ			=	$(addprefix %(DIR_OBJ),$(SRC_FILES:.c=.o))
OBJ_LXR		=	$(addprefix %(DIR_OBJ),$(SRC_LXR:.c=.o))
OBJ_PRS		=	$(addprefix %(DIR_OBJ),$(SRC_PRS:.c=.o))
OBJ_BLT		=	$(addprefix %(DIR_OBJ),$(SRC_BLT:.c=.o))
OBJ_EXP		=	$(addprefix %(DIR_OBJ),$(SRC_EXP:.c=.o))
OBJ_EXEC	=	$(addprefix %(DIR_OBJ),$(SRC_EXEC:.c=.o))
OBJ_PMT		=	$(addprefix %(DIR_OBJ),$(SRC_PMT:.c=.o))
OBJ_HRD		=	$(addprefix %(DIR_OBJ),$(SRC_HRD:.c=.o))

LIB_A		:=	$(DIR_LIB)libft.a
LIB_ADD_DIR :=	-L$(DIR_LIB)
LIB_SEARCH	:=	-lft 

# *******************************  HEADERS	******************************* #

HEADERS		:=	$(INC_ROOT)
HEADERS		+=	$(addsuffix $(INC_ROOT),$(DIR_LIB))

# *******************************  COLORS	******************************* #

RED			=	\033[0;31m
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
BLUE		=	\033[0;34m
PURPLE		=	\033[0;35m
CYAN		=	\033[0;36m
RESET		=	\033[0m
GREEN_BOLD	=	\033[1;32m
BLUE_BOLD	=	\033[1;34m
CYAN_BOLD	=	\033[1;36m

# ********************************	RULES	********************************** #

all	: library $(DIR_OBJ) $(NAME)

library	:
	@$(MAKE) -C $(DIR_LIB) --no-print-directory

$(NAME)	: $(OBJ) $(LXR_OBJ) $(BLT_OBJ) $(EXPAN_OBJ) $(EXEC_OBJ) $(PRS_OBJ) $(HRD_OBJ) $(PROM_OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LXR_OBJ) $(BLT_OBJ) $(EXPAN_OBJ) $(EXEC_OBJ) $(PRS_OBJ) $(HRD_OBJ) $(PROM_OBJ)

	@echo "${BLUE_BOLD}minishell ${GREEN}compiled successfully ✅\n${RESET}"

$(DIR_OBJ)%.o:	%.c Makefile $(LIB_A) $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -DREADLINE_LIBRARY=1 $(RDFLAGS) -c $< -o $@
	@echo "${YELLOW}Object compiling ${RESET}$@...${RESET}"

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

clean	:
	@$(MAKE) -C libft clean --no-print-directory
	@$(RM) $(DIR_OBJ)
	@echo "${RED}Deleting${RESET} all objects 🗑"

fclean	: clean
	@$(MAKE) -C libft clean --no-print-directory
	@$(RM) $(NAME)
	@printf "${RED}Minishell{RESET} deleted 🗑"

re		: fclean
	@$(MAKE) all

.PHONY	: all clean fclean re library