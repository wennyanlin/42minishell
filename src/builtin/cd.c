/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:26:59 by rtorrent          #+#    #+#             */
/*   Updated: 2024/10/29 13:59:40 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	test_first(char *directory, char *sequence)
{
	char *const	delim = ft_strchr(directory, SLASH);

	if (!delim)
		return (!ft_strncmp(directory, sequence, -1));
	return (!ft_strncmp(directory, sequence, delim - directory));
}

static int	previous_directory(t_data *data)
{
	char *const	oldpwd = get_from_env(data->env, "OLDPWD");
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
	char *const	home = get_from_env(data->env, "HOME");

	if (!home)
		return (error_message(EXIT_FAILURE, 3, SHNAME, "cd", "HOME not set"));
	return (bt_cd(2, (char *[3]){"cd", home, NULL}, data));
}

static int	access_cd(t_data *data, char *path, char *curpath, char *argv)
{
	char	pwd[PATH_MAX];

	if (path[0] != SLASH)
	{
		getcwd(pwd, PATH_MAX);
		ft_strlcat(pwd, "/", PATH_MAX);
		ft_strlcat(pwd, path, PATH_MAX);
		curpath = pwd;
	}
	if (access(curpath, F_OK) == INVALID)
		return (error_message(EXIT_FAILURE, 4, SHNAME, "cd", argv,
				"No such file or directory"));
	if (access(curpath, X_OK) == INVALID)
		return (error_message(EXIT_FAILURE, 4, SHNAME, "cd", argv,
				"Permission denied"));
	if (chdir(curpath) == INVALID)
		return (error_message(errno, 3, SHNAME, "cd", strerror(errno)));
	curpath = get_from_env(data->env, "PWD");
	if (curpath)
		set_in_env(&data->export_vars, "OLDPWD", curpath);
	else
		bt_unset(1, (char *[2]){"OLDPWD", NULL}, data);
	getcwd(pwd, PATH_MAX);
	set_in_env(&data->export_vars, "PWD", pwd);
	return (EXIT_SUCCESS);
}

int	bt_cd(int argc, char *argv[], t_data *data)
{
	char	path[PATH_MAX];
	char	*curpath;

	if (argc == 1)
		return (home_directory(data));
	else if (argc == 2 && !ft_strncmp(argv[1], "-", -1))
		return (previous_directory(data));
	else if (argc > 2)
		return (error_message(EXIT_FAILURE, 3, SHNAME, "cd",
				"too many arguments"));
	if (**++argv == SLASH || test_first(*argv, ".") || test_first(*argv, ".."))
		ft_strlcpy(path, *argv, PATH_MAX);
	else
	{
		curpath = find_cmd_path(data->env, "CDPATH", *argv);
		if (curpath)
			ft_strlcpy(path, curpath, PATH_MAX);
		else
		{
			ft_strlcpy(path, "./", PATH_MAX);
			ft_strlcat(path, *argv, PATH_MAX);
		}
		free(curpath);
	}
	return (access_cd(data, path, path, *argv));
}
