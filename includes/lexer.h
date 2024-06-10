/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:58:40 by wlin              #+#    #+#             */
/*   Updated: 2024/06/10 16:57:48 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef LEXER_H
# define LEXER_H

typedef enum s_token
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS
}	t_token;


typedef struct s_lst
{
	char			*value = "'hello'";
	int				need_expansion; //TRUE/FALSE
	t_token			type;
    struct s_lst	*prev;
	struct s_lst	*next;
}	t_lst;

int		is_whitespace(char c);
int		skip_spaces(char *str, int i);
t_lst	*init_lst_node(void);

# endif
