/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:27:19 by wlin              #+#    #+#             */
/*   Updated: 2024/07/11 16:36:03 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "macros.h"
#include "executor.h"

int lst_size(t_commands *cmds)
{
    int             i;
    t_commands		*tmp;
    
    i = 0;
    tmp = cmds;
	while (tmp)
	{
		++i;
		tmp = tmp->next;
	}
    return (i);
}