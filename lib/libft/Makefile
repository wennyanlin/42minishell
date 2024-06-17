# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/09 20:06:48 by wlin              #+#    #+#              #
#    Updated: 2024/06/17 16:29:38 by wlin             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INCLUDES = libft.h

SRCS =  ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
        ft_strlen.c ft_tolower.c ft_toupper.c ft_strchr.c ft_strlcpy.c \
		ft_strlcat.c ft_strrchr.c ft_strncmp.c ft_strnstr.c ft_bzero.c\
		ft_memchr.c ft_memset.c ft_memcpy.c ft_memcmp.c ft_memmove.c ft_atoi.c\
		ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c\
		ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
		ft_striteri.c ft_strmapi.c ft_split.c

SRCSBONUS = ft_tokennew_bonus.c ft_tokenadd_front_bonus.c ft_tokensize_bonus.c\
			ft_tokenlast_bonus.c ft_tokenadd_back_bonus.c ft_tokendelone_bonus.c\
			ft_tokenclear_bonus.c ft_tokeniter_bonus.c ft_tokenmap_bonus.c

OBJS = $(SRCS:.c=.o)

OBJSBONUS = $(SRCSBONUS:.c=.o)

COMPILER = cc

FLAGS = -Wall -Werror -Wextra

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

%.o: %.c Makefile ${INCLUDES}
	@$(COMPILER) $(FLAGS) -I $(INCLUDES) -c $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(NAME): $(OBJS) $(INCLUDES) Makefile
	@echo "\n\n${BLUE_BOLD}[libft] $(GREEN)object files were created$(RESET)"
	@ar -rcs $(NAME) $(OBJS)
	@echo "${BLUE_BOLD}[libft] $(GREEN)library was created$(RESET)\n"

bonus: $(OBJS) $(OBJSBONUS)
	ar -rcs $(NAME) $(OBJS) $(OBJSBONUS)

all: $(NAME)

clean:
	@rm -f $(OBJS) $(OBJSBONUS)

fclean: clean
	@rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
