/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:58:40 by wlin              #+#    #+#             */
/*   Updated: 2024/06/17 16:29:38 by wlin             ###   ########.fr       */
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


typedef struct s_token
{
	char			*word;
	t_metachar		metachar;
    struct s_token	*prev;
	struct s_token	*next;
}	t_token;

void	ft_error(char *input, int start);
void	printf_list(t_token *lst);
int		is_whitespace(char c);
int		skip_spaces(char *str, int i);
int		is_delimiter(char c);
t_token	*create_lst_node(char *word, int metachar);
void    lst_add_back(t_token **token_lst, t_token *new_node);
int		find_matching_quote(char *input, int i, char quote);
int		find_end_chars_index(char *input, int i);
t_token	*tokenize(char *input);
void	test_lexer(void);
void	ft_free_lst(t_token *lst);

# endif
