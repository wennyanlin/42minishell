/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:36:35 by rtorrent          #+#    #+#             */
/*   Updated: 2024/09/10 13:57:30 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define EXIT_ERROR 2
#define BUFFER_ERROR 128

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
	char	non_numeric[BUFFER_ERROR];

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (argc == 1)
		exit_minishell(data, NULL, NULL, data->exit_status);
	if (argc > 2)
		return (error_message("minishell: exit", "too many arguments",
				EXIT_ERROR));
	ft_strlcpy(non_numeric, *++argv, BUFFER_ERROR);
	ft_strlcat(non_numeric, ": numeric argument required", BUFFER_ERROR);
	n = atoi_version(&err, *argv);
	if (err)
		exit_minishell(data, "exit", non_numeric, EXIT_ERROR);
	exit_minishell(data, NULL, NULL, n);
	return (EXIT_SUCCESS);
}
