/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:06:59 by rtorrent          #+#    #+#             */
/*   Updated: 2024/08/28 13:22:21 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_name(char **ep)
{
	while (*ep)
	{
		*ep = ep[1];
		ep++;
	}
}

int	bt_unset(int argc, char *argv[])
{
	extern char	**environ;
	char		**ep;
	size_t		n;
	int			ret;

	if (!environ)
		return (-1);
	ret = 0;
	while (--argc)
	{
		n = ft_strlen(*++argv);
		ep = environ;
		while (*ep)
		{
			if (!ft_strncmp(*ep, *argv, n) && (*ep)[n] == '=')
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
