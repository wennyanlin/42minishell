/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 11:46:39 by wlin              #+#    #+#             */
/*   Updated: 2024/06/25 17:20:25 by wlin             ###   ########.fr       */
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
	array = NULL;
}

void	parse_command(t_exec_state *state)
{
    char    *env_value;

    env_value = getenv("PATH");
    state->cmd_path = find_path(env_value, state->cmd_args[0]);
    // free(env_value);
}

void	execute_command(char *command_path, char **cmd_args, char **envp, int pipe_fd[2])
{
	char	**result_array_concat = NULL;

	execve(command_path, cmd_args, envp);
	if (errno == ENOEXEC)
	{
		result_array_concat = array_concat("/bin/sh", cmd_args);
		execve("/bin/sh", result_array_concat, envp);
        close(pipe_fd[WR]);
		// free_array(re sult_array_concat);
		result_array_concat = NULL;
	}
	else if (errno == ENOENT)
	{
		if (char_index(cmd_args[0], '/') != INVALID)
        {
			perror(cmd_args[0]);
            close(pipe_fd[WR]);
        }
		else
		{
			write(STDERR_FILENO, cmd_args[0], str_size(cmd_args[0]));
			write(STDERR_FILENO, ": command not found\n", 20);
            close(pipe_fd[WR]);
			exit(127);
		}
	}
	else
    {
		perror_and_exit(cmd_args[0], EXIT_FAILURE);
        close(pipe_fd[WR]);
    }
}

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
        free(state.cmd_path);
        // free_array(state.cmd_args);
	}
}