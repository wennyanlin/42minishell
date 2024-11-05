/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:55:50 by rtorrent          #+#    #+#             */
/*   Updated: 2024/11/05 13:38:28 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define EXPORT_ERROR 2

static int	print_export_vars(char **vars)
{
	char	*equals;

	while (*vars)
	{
		printf("declare -x ");
		equals = ft_strchr(*vars, EQUALS);
		if (equals)
		{
			printf("%.*s", (int)(equals - *vars), *vars);
			printf("=\"");
			if (*++equals)
				printf("%s", equals);
			printf("\"\n");
		}
		else
			printf("%s\n", *vars);
		vars++;
	}
	return (EXIT_SUCCESS);
}

static void	export_arg(t_data *data, char arg[], int *error)
{
	char	*p;

	p = arg;
	if (ft_isalpha(*p) || *p == UNDERSCORE)
		while (ft_isalnum(*++p) || *p == UNDERSCORE)
			;
	if (!*p && get_from_env(data->env, arg))
		return ;
	else if (!*p || (*p == EQUALS && p != arg))
		export_var(&data->export_vars, arg, p);
	else
	{
		p = quote_str(arg);
		*error = error_message(EXIT_FAILURE, 4, SHNAME, "export", p,
				"not a valid identifier");
		free(p);
	}
}

int	bt_export(int argc, char *argv[], t_data *data)
{
	argc = EXIT_SUCCESS;
	if (*++argv && **argv == MINUS && (*argv)[1])
		return (error_message(EXPORT_ERROR, 4, SHNAME, "export",
				(char [3]){MINUS, (*argv)[1], '\0'}, "invalid option"));
	if (!*argv)
		return (print_export_vars(data->export_vars));
	while (*argv)
		export_arg(data, *argv++, &argc);
	return (argc);
}
