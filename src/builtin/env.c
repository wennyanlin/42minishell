/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:41:57 by rtorrent          #+#    #+#             */
/*   Updated: 2024/10/07 20:13:52 by rtorrent         ###   ########.fr       */
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
		return (error_message(ENV_ERROR, 3, "env", *++argv,
				"invalid option/argument"));
	if (ep)
		while (*ep)
			printf("%s\n", *ep++);
	return (EXIT_SUCCESS);
}
