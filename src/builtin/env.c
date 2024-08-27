/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:41:57 by rtorrent          #+#    #+#             */
/*   Updated: 2024/08/26 15:04:01 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bt_env(int argc, char *argv[])
{
	extern char	**environ;
	char		**ep;

	(void)argc;
	(void)argv;
	ep = environ;
	if (!ep)
		return (1);
	while (*ep)
		printf("%s\n", *ep++);
	return (0);
}
