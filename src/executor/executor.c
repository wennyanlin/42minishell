/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 11:46:39 by wlin              #+#    #+#             */
/*   Updated: 2024/08/01 11:09:54 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "macros.h"

int get_wait_status(int status)
{
    int stat_code;

    stat_code = 0;
    if (WIFEXITED(status))
        stat_code = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        stat_code = WTERMSIG(status);
    else if (WIFSTOPPED(status))
        stat_code = WSTOPSIG(status);
    return (stat_code);
}

void	wait_process(pid_t *pid_array, int num_cmd)
{
	int	i;
	int	status;

	i = -1;
	while (++i < num_cmd)
	{
		waitpid(pid_array[i], &status, 0);
		get_wait_status(status);
	}
}

void	execute_command(char *command_path, char **cmd_args, char **envp)
{
	char	**result_array_concat = NULL;

	execve(command_path, cmd_args, envp);
	if (errno == ENOEXEC)
	{
		result_array_concat = array_concat("/bin/sh", cmd_args);
		execve("/bin/sh", result_array_concat, envp);
	}
	else if (errno == ENOENT)
	{
		if (char_index(cmd_args[0], '/') != INVALID)
			perror(cmd_args[0]);
		else
		{
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, cmd_args[0], str_size(cmd_args[0]));
			write(STDERR_FILENO, ": command not found\n", 20);
			exit(127);
		}
	}
	else
		perror_and_exit(cmd_args[0], EXIT_FAILURE);
}

void	execute_all(t_commands *cmds, char **envp)
{
	t_process	process;
	pid_t		*pid;
	int			i;
	int			num_cmd;
	int			pipe_read_end_prev;

	i = -1;
	num_cmd = lst_size(cmds);
	pid = malloc(sizeof(pid_t) * num_cmd);
	pipe_read_end_prev = dup(STDIN_FILENO);
	while (cmds)
	{
		parameter_expansion(cmds->args);
		process = init_process(cmds, envp, pipe_read_end_prev);
		if (process.command != NULL)
		{
			if (is_builtin(process.command[0]) == EXIT_FAILURE)
			{
				pid[++i] = create_process(&process);
				free(process.cmd_path);
			}
		}
		cmds = cmds->next;
		pipe_read_end_prev = process.pipe_fd[RD];
	}
	wait_process(pid, num_cmd);
	free(pid);
}
