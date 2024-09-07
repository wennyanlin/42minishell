/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:41:57 by rtorrent          #+#    #+#             */
/*   Updated: 2024/09/07 18:50:46 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bt_env(int argc, char *argv[])
{
	char	**ep;

	(void)argc;
	(void)argv;
	ep = environ;
	if (!ep)
		return (1);
	while (*ep)
		printf("%s\n", *ep++);
	return (0);
}
