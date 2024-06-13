/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglanuss <aglanuss@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:44:59 by aglanuss          #+#    #+#             */
/*   Updated: 2024/06/13 14:12:12 by aglanuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

typedef struct	s_command
{
	char	**str;
	struct s_command	*prev;
	struct s_command	*next;
}								t_command;

/* DELETE THIS */
typedef enum e_token
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS
}	t_token;

typedef struct s_lexer
{
	char					*value;
	t_token				type;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}	t_lexer;
/* DELETE THIS */

t_command	*new_command_node(char **str);
void			add_command_node(t_command **commands_lst, t_command *new_command);
int count_words_until_pipe(t_lexer **lexer);

#endif