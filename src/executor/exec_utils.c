/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:27:19 by wlin              #+#    #+#             */
/*   Updated: 2024/09/18 19:25:46 by rtorrent         ###   ########.fr       */
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
		exit_minishell(data, "dup2", strerror(e), e);
	if (c == INVALID)
		exit_minishell(data, "close", strerror(errno), errno);
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
