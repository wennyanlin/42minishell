/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:58:40 by wlin              #+#    #+#             */
/*   Updated: 2024/06/11 17:25:59 by wlin             ###   ########.fr       */
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
	char			*value;
	t_token			token;
    struct s_lst	*prev;
	struct s_lst	*next;
}	t_lst;

int		is_whitespace(char c);
int		skip_spaces(char *str, int i);
t_lst	*init_lst_node(void);
t_lst	*create_lst_node(char *word, int token);
void    lst_add_back(t_lst **token_lst, t_lst *new_node);
int		find_matching_quote(char *input, int i, char quote);
int		find_end_chars_index(char *input, int i);
void	handle_input(char *input);

# endif
