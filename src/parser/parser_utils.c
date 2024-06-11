/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglanuss <aglanuss@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:30:11 by aglanuss          #+#    #+#             */
/*   Updated: 2024/06/11 12:52:52 by aglanuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_command *new_command_node(char **str)
{
  t_command *node;

  node = malloc(sizeof(t_command));
  if (!node)
    return (NULL);
  node->str = str;
  node->prev = NULL;
  node->next = NULL;
  return (node);
}

void  add_command_node(t_command **commands_lst, t_command *new_command)
{
  t_command *last_node;

  if (!commands_lst)
    return ;
  if (!*commands_lst)
    *commands_lst = new_command;
  else
  {
    last_node = *commands_lst;
    while(last_node->next)
      last_node = last_node->next;
    last_node->next = new_command;
  }
}