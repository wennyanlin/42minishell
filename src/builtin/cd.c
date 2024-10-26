/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:26:59 by rtorrent          #+#    #+#             */
/*   Updated: 2024/10/26 18:40:02 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	previous_directory(t_data *data)
{
	char *const	oldpwd = getenvp(data->export_vars, "OLDPWD");
	int			ret1;
	int			ret2;

	if (!oldpwd)
		return (error_message(EXIT_FAILURE, 3, SHNAME, "cd", "OLDPWD not set"));
	ret1 = bt_cd(2, (char *[3]){"cd", oldpwd, NULL}, data);
	ret2 = bt_pwd(1, (char *[2]){"pwd", NULL}, data);
	
// TODO: return value of `cd "$OLDPWD" && pwd'
}

int	bt_cd(int argc, char *argv[], t_data *data)
{
	if (argc == 2 && ft_strncmp(*argv[1], "-", -1))
		return (previous_directory(data));


	return (0);
}
