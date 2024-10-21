/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:41:57 by rtorrent          #+#    #+#             */
/*   Updated: 2024/10/21 17:43:21 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ENV_ERROR 125

int	bt_env(int argc, char *argv[], t_data *data)
{
	char	**ep;

	ep = data->export_vars;
	if (argc > 1)
		return (error_message(ENV_ERROR, 3, "env", *++argv,
				"invalid option/argument"));
	if (ep)
	{
		while (*ep)
		{
			if (ft_strchr(*ep, EQUALS))
				ft_putendl_fd(*ep, STDOUT_FILENO);
			ep++;
		}
	}
	return (EXIT_SUCCESS);
}
