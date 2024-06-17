/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:58:40 by wlin              #+#    #+#             */
/*   Updated: 2024/06/17 14:34:07 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef LEXER_H
# define LEXER_H

typedef enum s_metachar
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS
}	t_metachar;


typedef struct s_lst
{
	char			*word;
	t_metachar		metachar;
    struct s_lst	*prev;
	struct s_lst	*next;
}	t_lst;

void	ft_error(char *input, int start);
void	printf_list(t_lst *lst);
int		is_whitespace(char c);
int		skip_spaces(char *str, int i);
int		is_delimiter(char c);
t_lst	*create_lst_node(char *word, int metachar);
void    lst_add_back(t_lst **token_lst, t_lst *new_node);
int		find_matching_quote(char *input, int i, char quote);
int		find_end_chars_index(char *input, int i);
t_lst	*tokenize(char *input);
void	test_lexer(void);
void	ft_free_lst(t_lst *lst);

# endif
