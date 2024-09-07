/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:06:59 by rtorrent          #+#    #+#             */
/*   Updated: 2024/09/07 18:51:20 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_name(char **ep)
{
	char **const	ep0 = ep;

	while (*ep)
	{
		if (ep == ep0)
			free(*ep);
		*ep = ep[1];
		ep++;
	}
}

int	bt_unset(int argc, char *argv[])
{
	char	**ep;
	size_t	n;
	int		ret;

	if (!environ)
		return (-1);
	ret = 0;
	while (--argc)
	{
		n = ft_strlen(*++argv);
		ep = environ;
		while (*ep)
		{
			if (!ft_strncmp(*ep, *argv, n) && (*ep)[n] == EQUALS)
			{
				remove_name(ep);
				ret--;
				break ;
			}
			ep++;
		}
		ret++;
	}
	return (ret);
}
