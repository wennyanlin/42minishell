/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 11:46:39 by wlin              #+#    #+#             */
/*   Updated: 2024/06/25 00:24:35 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "macros.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	parse_command(t_exec_state *state)
{
    char    *env_value;

    env_value = getenv("PATH");
    state->cmd_path = find_path(env_value, state->cmd_args[0]);
    // free(env_value);
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

// void    executor(char **cmd_args, char **envp)
// {
//     char    *cmd_path;
    
//     execute_command(cmd_path, cmd_args, envp);
// }

// void init_state(t_exec_state *state)
// {
// 	state->cmd_args = 
// }

void	execute_all(char **cmd_arr, char **envp)
{
	t_exec_state	state;
	int				i;

	i = 0;
	while (cmd_arr[i])
		i++;
	state.fd_in = dup(STDIN_FILENO);
	state.envp = envp;
	state.cmd_args = cmd_arr;
	state.num_cmds = i;
	i = -1;
	state.cmd_idx = &i;
	while (state.cmd_args[++i])
	{
    	parse_command(&state);
		create_process(&state);
        // free(state->cmd_path);
        // free_array(state->cmd_args);
	}
}