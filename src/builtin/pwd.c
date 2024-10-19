/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:06:28 by rtorrent          #+#    #+#             */
/*   Updated: 2024/10/19 14:59:13 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PWD_ERROR 2

int	bt_pwd(int argc, char *argv[], t_data *data)
{
	char	pwd[PATH_MAX];

	(void)data;
	if (argc > 1)
		return (error_message(PWD_ERROR, 3, "pwd", *++argv, "invalid option"));
	if (getcwd(pwd, PATH_MAX))
		ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
