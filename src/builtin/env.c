/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:41:57 by rtorrent          #+#    #+#             */
/*   Updated: 2024/09/08 14:57:14 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ENV_ERROR 125

int	bt_env(int argc, char *argv[], t_data *data)
{
	char	**ep;

	(void)argv;
	(void)data;
	ep = environ;
	if (argc > 1)
		return (error_message("env", "invalid option/argument", ENV_ERROR));
	if (ep)
		while (*ep)
			printf("%s\n", *ep++);
	return (EXIT_SUCCESS);
}
