/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:27:19 by wlin              #+#    #+#             */
/*   Updated: 2024/10/07 18:46:02 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fd_dup2(t_data *data, int oldfd, int newfd)
{
	int	c;
	int	d;
	int	e;

	d = dup2(oldfd, newfd);
	if (d == INVALID)
		e = errno;
	c = close(oldfd);
	if (d == INVALID)
		exit_minishell(data, e, 3, SHNAME, "dup2", strerror(e));
	if (c == INVALID)
		exit_minishell(data, errno, 3, SHNAME, "close", strerror(errno));
}

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
