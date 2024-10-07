/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:36:35 by rtorrent          #+#    #+#             */
/*   Updated: 2024/10/07 20:13:36 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	atoi_version(int *err, char *str)
{
	int	n;
	int	sign;

	while (is_whitespace(*str))
		str++;
	sign = *str == '-';
	if (*str == '-' || *str == '+')
		str++;
	n = 0;
	while (ft_isdigit(*str))
	{
		n *= 10;
		if (sign)
			n -= *str++ - '0';
		else
			n += *str++ - '0';
	}
	*err = *str;
	return (n);
}

int	bt_exit(int argc, char *argv[], t_data *data)
{
	int		n;
	int		err;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (argc == 1)
		exit_minishell(data, data->exit_status, 0);
	n = atoi_version(&err, *++argv);
	if (err)
		exit_minishell(data, EXIT_FAILURE, 4, SHNAME, "exit", *argv,
			"numeric argument required");
	if (argc > 2)
		return (error_message(EXIT_FAILURE, 3, SHNAME, "exit",
				"too many arguments"));
	exit_minishell(data, n, 0);
	return (EXIT_SUCCESS);
}
