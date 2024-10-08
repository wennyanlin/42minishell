/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:06:28 by rtorrent          #+#    #+#             */
/*   Updated: 2024/10/07 19:06:43 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PWD_ERROR 2

int	bt_pwd(int argc, char *argv[], t_data *data)
{
	char	buffer[PATH_MAX];
	char	*pwd;

	(void)argv;
	(void)data;
	if (argc > 1)
		return (error_message(PWD_ERROR, 3, "pwd", *++argv, "invalid option"));
	if (getcwd(buffer, PATH_MAX))
		pwd = buffer;
	else
		pwd = getenv("PWD");
	printf("%s\n", pwd);
	return (EXIT_SUCCESS);
}
