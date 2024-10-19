/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:06:59 by rtorrent          #+#    #+#             */
/*   Updated: 2024/10/19 14:57:23 by rtorrent         ###   ########.fr       */
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
		ep[0] = ep[1];
		ep++;
	}
}

int	bt_unset(int argc, char *argv[], t_data *data)
{
	char	**ep;
	size_t	n;

	if (!data->envp)
		return (EXIT_FAILURE);
	while (--argc)
	{
		n = ft_strlen(*++argv);
		ep = data->envp;
		while (*ep)
		{
			if (!ft_strncmp(*ep, *argv, n) && (*ep)[n] == EQUALS)
			{
				remove_name(ep);
				break ;
			}
			ep++;
		}
	}
	return (EXIT_SUCCESS);
}
