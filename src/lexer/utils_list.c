/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:59:45 by wlin              #+#    #+#             */
/*   Updated: 2024/06/09 23:39:44 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "macros.h"

t_lst	*create_lst_node(void)
{
	t_lst   *node;
    
    node = malloc(sizeof(t_lst));
    if (!node)
        exit(EXIT_FAILURE);
    node->value = NULL;
    node->next = NULL;
    node->prev = NULL;
    return (node);
}

