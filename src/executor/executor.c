/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 11:46:39 by wlin              #+#    #+#             */
/*   Updated: 2024/06/22 16:23:57 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "macros.h"

void	perror_and_exit(char *file, int code)
{
	perror(file);
	exit(code);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

char    *parse_command(char **cmd_args)
{
    char    *env_value;
    char    *cmd_path;

    env_value = getenv("PATH");
    cmd_path = find_path(env_value, cmd_args[0]);
    // free(env_value);
    return (cmd_path);
}

void	execute_command(char *command_path, char **cmd_args, char **envp)
{
	char	**result_array_concat = NULL;

	execve(command_path, cmd_args, envp);
	if (errno == ENOEXEC)
	{
		result_array_concat = array_concat("/bin/sh", cmd_args);
		execve("/bin/sh", result_array_concat, envp);
		// free_array(re sult_array_concat);
		result_array_concat = NULL;
	}
	else if (errno == ENOENT)
	{
		if (char_index(cmd_args[0], '/') != INVALID)
			perror(cmd_args[0]);
		else
		{
			write(STDERR_FILENO, cmd_args[0], str_size(cmd_args[0]));
			write(STDERR_FILENO, ": command not found\n", 20);
			exit(127);
		}
	}
	else
		perror_and_exit(cmd_args[0], EXIT_FAILURE);
}

void    executor(char **cmd_args, char **envp)
{
    char    *cmd_path;
    
    cmd_path = parse_command(cmd_args);
    if (access(cmd_path, X_OK) == -1 && access(cmd_path, F_OK) == 0)
    {
        write(STDERR_FILENO, cmd_args[0], str_size(cmd_args[0]));
        write(STDERR_FILENO, ": permission denied\n", 20);
        exit (126);
    }
    execute_command(cmd_path, cmd_args, envp);
}