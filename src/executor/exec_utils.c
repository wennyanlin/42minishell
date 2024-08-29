/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:27:19 by wlin              #+#    #+#             */
/*   Updated: 2024/08/28 21:06:32 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lst_size(t_commands *cmds)
{
	int			i;
	t_commands	*tmp;

	i = 0;
	tmp = cmds;
	while (tmp)
	{
		++i;
		tmp = tmp->next;
	}
	return (i);
}

int	directory_error(char *cmd)
{
	if (is_equal(".", cmd) == EXIT_SUCCESS)
		return (127);
	if (is_equal("/", cmd) == EXIT_SUCCESS)
		return (126);
	return (0);
}
