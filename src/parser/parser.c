/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglanuss <aglanuss@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:49:09 by aglanuss          #+#    #+#             */
/*   Updated: 2024/06/21 11:57:22 by aglanuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

char  **extract_words_from_lexer(t_lexer **lexer_lst)
{
  char  **words;
  int   words_num;
  int   i;

  if (!lexer_lst || !*lexer_lst)
    return (NULL);
  words_num = count_words_until_pipe(lexer_lst);
  words = (char **)malloc(sizeof(char *) * (words_num + 1));
  if (!words)
    return (NULL);
  words[words_num] = NULL;
  i = 0;
  while (i < words_num)
  {
    words[i] = ft_strdup((*lexer_lst)->value);
    // todo: free words array in case of error.
    if (!words[i])
      return (NULL);
    remove_first_node_lexer(lexer_lst);
    i++;
  }
  remove_first_node_lexer(lexer_lst);
  return (words);
}

// t_command **create_commands(t_lexer **lexer_lst)
// {
//   t_command **commands_list;
//   t_command *new_command;

//   commands_list = NULL;
//   while (*lexer_lst)
//   {

//     new_command = new_command_node();
//   }
// }

// t_command **parse_input(t_lexer **lexer_lst)
// {
//   t_command **commands_list;

//   if (!lexer_lst || !*lexer_lst)
//     return (NULL);
//   commands_list = create_commands(lexer_lst);
//   if (!commands_list)
//     return (NULL);
//   return (commands_list);
// }
