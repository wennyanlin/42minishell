/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_find_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 13:12:56 by wlin              #+#    #+#             */
/*   Updated: 2024/08/12 16:54:02 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL || *array == NULL)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
	array = NULL;
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

char *make_path(char *dir, char *cmd)
{
	char *full_dir;
	char *full_path;

	full_dir = string_concat(dir, "/");
	full_path = string_concat(full_dir, cmd);
	free(full_dir);
	return (full_path);
}

int	directory_error(char *cmd)
{
	if (is_equal(".", cmd) == EXIT_SUCCESS)
	{
		// printf("minishell: .: command not found\n");
		return (127);
	}
	if (is_equal("/", cmd) == EXIT_SUCCESS)
	{
		// printf("minishell: /: is a directory\n");
		return (126);
	}
	return (0);
}

char	*find_cmd_path(char *env, char *cmd)
{
	int		i;
	int		exit_code;
	char 	*full_path;
	char 	**path_dirs;

	if (!env)
		return (str_cpy(cmd));	
	if (char_index(cmd, '/') != NOT_FOUND)
		return (str_cpy(cmd));
	exit_code = directory_error(cmd);
	if (exit_code != 0)
		return (cmd);
	path_dirs = split_path(env, ':');
	i = -1;
	while (path_dirs[++i])
	{
		full_path = make_path(path_dirs[i], cmd);
		// printf("full_path = %s\n", full_path);
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
