/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:06:28 by rtorrent          #+#    #+#             */
/*   Updated: 2024/08/27 14:53:48 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bt_pwd(int argc, char *argv[])
{
	char	buffer[PATH_MAX];
	char	*pwd;

	(void)argc;
	(void)argv;
	if (getcwd(buffer, PATH_MAX))
		pwd = buffer;
	else
		pwd = getenv("PWD");
	printf("%s\n", pwd);
	return (0);
}
