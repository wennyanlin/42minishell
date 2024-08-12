/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:18:58 by wlin              #+#    #+#             */
/*   Updated: 2024/08/12 16:53:31 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands  *create_cmd_lstnew()
{
    t_commands  *new;

    new = malloc(sizeof(t_commands));
    if (!new)
        return (NULL);
    new->args = NULL;
    new->redirect = NULL;
    new->prev = NULL;
    new->next = NULL;
    return (new);
}

void    cmd_lst_addback(t_commands **cmds, t_commands *new)
{
    t_commands  *tmp;

    if (*cmds != NULL)
    {
        tmp = *cmds;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
        new->prev = tmp;
    }
    else
    {
        (*cmds) = new;
    }
}

int    count_cmd_str(t_token *tokens)
{
    t_token *tmp;
    int     len;

    tmp = tokens;
    len = 0;

    while (tmp && tmp->metachar != PIPE)
    {
        if (tmp->metachar > PIPE)
            tmp = tmp->next;
        else
            ++len;
        tmp = tmp->next;
    }
    return (len);
}

int is_redirection(t_metachar type)
{
    if (type == LESS || type == LESS_LESS 
            || type == GREAT || type == GREAT_GREAT)
        return (1);
    else
        return (0);           
}
