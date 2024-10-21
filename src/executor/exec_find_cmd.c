/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_find_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 13:12:56 by wlin              #+#    #+#             */
/*   Updated: 2024/10/21 17:11:55 by rtorrent         ###   ########.fr       */
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
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
	}
	return (NULL);
}

char	*find_cmd_path(t_data *data, char *cmd)
{
	char *const	env = getenvp(data->export_vars, "PATH");
	char		*full_path;
	char		**path_dirs;

	if (!env)
		return (ft_strdup(cmd));
	if (char_index(cmd, '/') != NOT_FOUND)
		return (ft_strdup(cmd));
	path_dirs = split_path(env, ':');
	full_path = examine_path(path_dirs, cmd);
	data->cmd_path = full_path;
	array_clear(&path_dirs);
	if (full_path == NULL)
		exit_minishell(data, NOTFOUND, 2, cmd, "command not found");
	return (full_path);
}
