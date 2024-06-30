/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:38:17 by wlin              #+#    #+#             */
/*   Updated: 2024/06/30 19:39:44 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MACROS_H
# define MACROS_H


# define SP 40

# define VERSION "0.1"
# define BLUE "\033[1;34m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"
# define NAME "minishell"
# define PROMPT BLUE NAME "% " RESET
# define HEREDOC_PROMPT "> "

# define TRUE 1
# define FALSE 0
# define UNINITIALIZED -1
# define NOT_FOUND -1
# define INVALID -1
# define NONE 0

# define QUOTE_S 39
# define QUOTE_D 34
# define DOLLAR 36
# define C_PIPE 124
# define C_LESS 60
# define C_GREAT 62

#define EXIT_FAILURE 1

# define NEGATIVE 0
# define CHILD 0
# define WR 1
# define RD 0

# endif
