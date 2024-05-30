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
HEADER		:= ./includes/minishell.h

DIR_OBJ		:=	obj/
DIR_SRC		:=	src/
DIR_RDL		:=	readline/
DIR_LIB		:=	libft/
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

# ********************************	RULES	********************************** #

