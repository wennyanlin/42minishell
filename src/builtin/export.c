/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:55:50 by rtorrent          #+#    #+#             */
/*   Updated: 2024/10/25 22:41:08 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define EXPORT_ERROR 2

static int	print_export_vars(char **vars)
{
	char	*equals;

	while (*vars)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		equals = ft_strchr(*vars, EQUALS);
		if (equals)
		{
			dprintf(STDOUT_FILENO, "%.*s", (int)(equals - *vars), *vars);
			ft_putstr_fd("=\"", STDOUT_FILENO);
			if (*++equals)
				ft_putstr_fd(equals, STDOUT_FILENO);
			ft_putendl_fd("\"", STDOUT_FILENO);
		}
		else
			ft_putendl_fd(*vars, STDOUT_FILENO);
		vars++;
	}
	return (EXIT_SUCCESS);
}

int	bt_export(int argc, char *argv[], t_data *data)
{
	char	*p;

	argc = EXIT_SUCCESS;
	if (*++argv && **argv == MINUS && (*argv)[1])
		return (error_message(EXPORT_ERROR, 4, SHNAME, "export",
				(char [3]){MINUS, (*argv)[1], '\0'}, "invalid option"));
	if (!*argv)
		return (print_export_vars(data->export_vars));
	while (*argv)
	{
		p = *argv;
		if (ft_isalpha(*p) || *p == UNDERSCORE)
			while (ft_isalnum(*++p) || *p == UNDERSCORE)
				;
		if (!*p || *p == EQUALS)
			export_var(&data->export_vars, *argv++, p);
		else
		{
			p = quote_str(*argv++);
			argc = error_message(EXIT_FAILURE, 4, SHNAME, "export", p,
					"not a valid identifier");
			free(p);
		}
	}
	return (argc);
}
