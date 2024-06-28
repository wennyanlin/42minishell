/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 13:12:56 by wlin              #+#    #+#             */
/*   Updated: 2024/06/28 20:47:57 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "macros.h"
#include "minishell.h"

char	**array_concat(char *shell_path, char **args)
{
	char 	**result_args;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (args[len])
		len++;
	result_args = malloc(sizeof(char*) * (len + 2));
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

char	*str_cpy(char *src)
{
	int	i;
	int	src_len;
	char *copy;

	i = -1;
	src_len = str_size(src);
	copy = malloc(sizeof(char) * (src_len + 1));
	if (!copy)
		return (NULL);
	while (src[++i])
		copy[i] = src[i];
	copy[i] = '\0';
	return (copy);
}

int	char_index(char *str, char ref)
{
	int	i;

	i = -1;
	if (!*str || !str)
		return (-1);
	while (str[++i])
		if (str[i] == ref)
			return (i);
	return (-1);
}

int	str_size(const char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return(len);
}

char	*string_concat(char *path, char *cmd)
{
	char 	*result_path;
	size_t	path_len;
	size_t	cmd_len;
	size_t	total_len;
	size_t	i;

	path_len = str_size(path);
	cmd_len = str_size(cmd);
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

char *make_path(char *dir, char *cmd)
{
	char *full_dir;
	char *full_path;

	full_dir = string_concat(dir, "/");
	full_path = string_concat(full_dir, cmd);
	free(full_dir);
	return (full_path);
}

char	*find_cmd_path(char *env, char *cmd)
{
	int		i;
	char 	*full_path;
	char 	**path_dirs;

	if (!env)
		return (str_cpy(cmd));	
	if (char_index(cmd, '/') != NOT_FOUND)
		return (str_cpy(cmd));
	path_dirs = split_path(env, ':');
	i = -1;
	while (path_dirs[++i])
	{
		full_path = make_path(path_dirs[i], cmd);
		if (access(full_path, X_OK) == 0)
		{
			free_array(path_dirs);
			return (full_path);
		}
		free(full_path);
		full_path = NULL;
	}
	free_array(path_dirs);
	path_dirs = NULL;
	return (str_cpy(cmd));
}

