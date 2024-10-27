/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:26:59 by rtorrent          #+#    #+#             */
/*   Updated: 2024/10/27 21:15:30 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*test_cdpath(char **pcurpath, char *directory)
{
//TODO: split de CDPATH
	*pcurpath = ft_strdup(*pcurpath);
	return (*pcurpath);
}

static int	previous_directory(t_data *data)
{
	char *const	oldpwd = getenvp(data->export_vars, "OLDPWD");
	int			ret;

	if (!oldpwd)
		return (error_message(EXIT_FAILURE, 3, SHNAME, "cd", "OLDPWD not set"));
	ret = bt_cd(2, (char *[3]){"cd", oldpwd, NULL}, data);
	if (ret)
		return (ret);
	return (bt_pwd(1, (char *[2]){"pwd", NULL}, data));
}

static int	home_directory(t_data *data)
{
	char *const	home = getenvp(data->export_vars, "HOME");

	if (!home)
		return (error_message(EXIT_FAILURE, 3, SHNAME, "cd", "HOME not set"));
	return (bt_cd(2, (char *[3]){"cd", home, NULL}, data));
}

int	bt_cd(int argc, char *argv[], t_data *data)
{
	char	**directory;
	char	*curpath;

	if (argc == 1)
		return (home_directory(data));
	else if (argc == 2 && ft_strncmp(*argv[1], "-", -1))
		return (previous_directory(data));
	if (argc > 2 || !test_cdpath(&curpath, argv[1]));
		return (error_message(EXIT_FAILURE, 3, SHNAME, "cd",
				"too many arguments"));
	curpath = test_cdpath(argv[1]);
	directory = ft_split(argv[1], SLASH);
	if (!directory)
		exit_minishell(data, errno, 3, SHNAME, "cd", strerror(errno));
	free(curpath);
	array_clear(&directory);
	return (0);
}
