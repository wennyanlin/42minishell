/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_find_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 13:12:56 by wlin              #+#    #+#             */
/*   Updated: 2024/08/26 14:00:31 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*string_concat(char *path, char *cmd)
{
	char	*result_path;
	size_t	path_len;
	size_t	cmd_len;
	size_t	total_len;
	size_t	i;

	if (path == NULL || cmd == NULL)
		return (NULL);
	path_len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	total_len = path_len + cmd_len;
	result_path = malloc(sizeof(char) * (total_len + 1));
	if (!result_path)
		return (NULL);
	i = -1;
	while (++i < path_len)
		result_path[i] = path[i];
	cmd_len = 0;
	while (i < total_len)
		result_path[i++] = cmd[cmd_len++];
	result_path[i] = '\0';
	return (result_path);
}

char	**array_concat(char *shell_path, char **args)
{
	char	**result_args;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (args[len])
		len++;
	result_args = malloc(sizeof(char *) * (len + 2));
	if (!result_args)
		return (NULL);
	result_args[i] = shell_path;
	i++;
	while (i < len + 1)
	{
		result_args[i] = args[i - 1];
		i++;
	}
	result_args[i] = NULL;
	return (result_args);
}

char	*make_path(char *dir, char *cmd)
{
	char	*full_dir;
	char	*full_path;

	full_dir = string_concat(dir, "/");
	full_path = string_concat(full_dir, cmd);
	free(full_dir);
	return (full_path);
}

char	*examine_path(char **path_dirs, char *cmd)
{
	int		i;
	char	*full_path;

	i = -1;
	if (path_dirs == NULL)
		return (NULL);
	while (path_dirs[++i])
	{
		full_path = make_path(path_dirs[i], cmd);
		if (access(full_path, X_OK) == 0)
		{
			free_array(path_dirs);
			break ;
		}
		free(full_path);
		full_path = NULL;
	}
	return (full_path);
}

char	*find_cmd_path(char *cmd)
{
	char *const	env = getenv("PATH");
	int			exit_code;
	char		*full_path;
	char		**path_dirs;

	if (!env)
		return (ft_strdup(cmd));
	if (char_index(cmd, '/') != NOT_FOUND)
		return (ft_strdup(cmd));
	exit_code = directory_error(cmd);
	if (exit_code != 0)
		return (ft_strdup(cmd));
	path_dirs = split_path(env, ':');
	full_path = examine_path(path_dirs, cmd);
	if (full_path != NULL)
		return (full_path);
	free_array(path_dirs);
	path_dirs = NULL;
	return (ft_strdup(cmd));
}
