/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 11:46:39 by wlin              #+#    #+#             */
/*   Updated: 2024/06/30 19:56:20 by wlin             ###   ########.fr       */
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

t_process	init_process(t_commands *cmds, char **envp, int pipe_read_end_prev)
{
	t_process	process;

	process.envp = envp;
	process.command = cmds->str;
	process.cmd_path = find_cmd_path(getenv("PATH"), process.command[0]);
	process.fd_in = pipe_read_end_prev;
	if (cmds->redirect)
	{
		if (pipe(process.pipe_fd) == INVALID)
        	perror_and_exit("pipe", EXIT_FAILURE);
		if (cmds->redirect->type == GREAT)
			process.fd_out = open(cmds->redirect->filename, O_CREAT | O_TRUNC
				| O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if (cmds->redirect->type == GREAT_GREAT)
			process.fd_out = open(cmds->redirect->filename, O_CREAT | O_APPEND
				| O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if (cmds->redirect->type == LESS)
			process.fd_in = open(cmds->redirect->filename, O_RDONLY);
		else if (cmds->redirect->type == LESS_LESS)
			process.fd_in = read_here_doc(cmds->redirect->filename);
	}
	else if (cmds->next)
	{
		if (pipe(process.pipe_fd) == INVALID)
        	perror_and_exit("pipe", EXIT_FAILURE);
		process.fd_out = process.pipe_fd[WR];
	}
	else
		process.fd_out = dup(STDOUT_FILENO);
	return (process);
}

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

void	execute_all(t_commands *cmds, char **envp)
{
	t_commands	*tmp;
	t_process	process;
	pid_t		*pid;
	int			i;
	int			num_cmd;
	int			pipe_read_end_prev;
	
	i = -1;
	tmp = cmds;
	num_cmd = lst_size(tmp);
	pid = calloc(num_cmd, sizeof(pid_t));
	pipe_read_end_prev = dup(STDIN_FILENO);
	while (tmp)
	{
		process = init_process(tmp, envp, pipe_read_end_prev);
		pid[++i] = create_process(&process);
        free(process.cmd_path);
		tmp = tmp->next;
		pipe_read_end_prev = process.pipe_fd[RD];
        // free_array(process.command);
	}
	wait_process(pid, num_cmd);
}
