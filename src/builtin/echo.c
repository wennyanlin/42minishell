/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:09:53 by rtorrent          #+#    #+#             */
/*   Updated: 2024/10/19 15:08:31 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  echo option flags:
    FLN: 'n'
*/

#define FLN 01

static unsigned int	read_options(char ***pargv)
{
	unsigned int	option_flags;
	unsigned int	tentative_flags;
	char			*p;

	option_flags = 0;
	while (*++(*pargv) && ***pargv == MINUS)
	{
		tentative_flags = 0;
		p = **pargv;
		while (*++p && *p == 'n')
			tentative_flags |= FLN;
		if (*p || !tentative_flags)
			break ;
		option_flags |= tentative_flags;
	}
	return (option_flags);
}

int	bt_echo(int argc, char *argv[], t_data *data)
{
	const unsigned int	flags = read_options(&argv);

	(void)argc;
	(void)data;
	while (*argv)
	{
		ft_putstr_fd(*argv++, STDOUT_FILENO);
		if (*argv)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!(flags & FLN))
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
