/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:59:45 by wlin              #+#    #+#             */
/*   Updated: 2024/06/10 13:55:37 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "macros.h"

t_lst	*create_lst_node(char *new_token)
{
	t_lst   *node;
    
    node = malloc(sizeof(t_lst));
    if (!node)
        exit(EXIT_FAILURE);
    node->value = new_token;
    node->next = NULL;
    node->prev = NULL;
    return (node);
}

void    lst_add_back(t_lst **token_lst, t_lst *new_node)
{
    t_lst   *tmp;

    if (*token_lst)
    {
        tmp = token_lst;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_node;
        new_node->prev = tmp;
    }
    else
        *token_lst = new_node;
}