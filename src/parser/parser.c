/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglanuss <aglanuss@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:49:09 by aglanuss          #+#    #+#             */
/*   Updated: 2024/06/13 13:59:38 by aglanuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

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

void create_command(t_command **command_nodes, t_list **lexer_node)
{
  t_command *new_command;

  if ((*lexer_node))
  new_command = new_command_node();
}

t_command **parse_input(t_lexer **lexer_lst)
{
  t_list    *curr_lexer_node;
  t_command **commands_list;

  if (!lexer_lst || !*lexer_lst)
    return (NULL);
  curr_lexer_node = *lexer_lst;
  commands_list = NULL;
  while (curr_lexer_node)
    create_command(commands_list, &curr_lexer_node);
}
