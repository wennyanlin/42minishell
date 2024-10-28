/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:26:59 by rtorrent          #+#    #+#             */
/*   Updated: 2024/10/28 19:30:56 by rtorrent         ###   ########.fr       */
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
	char *const	oldpwd = ft_getenv(data->export_vars, "OLDPWD");
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
	char *const	home = ft_getenv(data->export_vars, "HOME");

	if (!home)
		return (error_message(EXIT_FAILURE, 3, SHNAME, "cd", "HOME not set"));
	return (bt_cd(2, (char *[3]){"cd", home, NULL}, data));
}

int	bt_cd(int argc, char *argv[], t_data *data)
{
	char	*curpath;

	if (argc == 1)
		return (home_directory(data));
	else if (argc == 2 && ft_strncmp(*argv[1], "-", -1))
		return (previous_directory(data));
	else if (argc > 2);
		return (error_message(EXIT_FAILURE, 3, SHNAME, "cd",
				"too many arguments"));
	if (**++argv == SLASH || test_first(*argv, ".") || test_first(*argv, "..")) 
		curpath = ft_strdup(*argv);
	else
	{
		curpath = find_cmd_path(data->env, "CDPATH", *argv);
		if (!cur_path)
			curpath = ft_strjoin("./", *argv);
	}
	if (!curpath)
		exit_minishell
//TODO: ***		

	if (curpath && access(curpath, F_OK) == INVALID)
		return (error_message(EXIT_FAILURE, 4, SHNAME, "cd", *argv,
				"No such file or directory");
	if (curpath && access(curpath, X_OK) == INVALID)
		return (error_message(EXIT_FAILURE, 4, SHNAME, "cd", *argv,
				"Permission denied");

	free(curpath);
	return (0);
}
