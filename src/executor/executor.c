/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 11:46:39 by wlin              #+#    #+#             */
/*   Updated: 2024/08/26 19:32:38 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_command(t_process *process, int pipe_read_end_prev,
		t_commands *cmds, t_data *data)
{
	shell_expansion(cmds->args, data);
	init_process(process, cmds, pipe_read_end_prev);
	if (process->command != NULL && process->fd_out != -1)
	{
		process->pipe_fd[RD] = dup(STDIN_FILENO);
		process->pipe_fd[WR] = dup(STDOUT_FILENO);
		fd_dup2(process->fd_in, STDIN_FILENO);
		fd_dup2(process->fd_out, STDOUT_FILENO);
		close(process->fd_in);
		close(process->fd_out);
		(*process->builtin)(array_len(process->command), process->command);
		fd_dup2(process->pipe_fd[RD], STDIN_FILENO);
		fd_dup2(process->pipe_fd[WR], STDOUT_FILENO);
		close(process->pipe_fd[RD]);
		close(process->pipe_fd[WR]);
	}
}

int	get_wait_status(int status)
{
	int	stat_code;

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

void	execute_command(char *command_path, char **cmd_args)
{
	extern char	**environ;
	char		**result_array_concat;

	result_array_concat = NULL;
	execve(command_path, cmd_args, environ);
	if (errno == ENOEXEC)
	{
		result_array_concat = array_concat("/bin/sh", cmd_args);
		execve("/bin/sh", result_array_concat, environ);
	}
	else if (errno == ENOENT)
	{
		if (char_index(cmd_args[0], '/') != INVALID)
			perror(cmd_args[0]);
		else
		{
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, cmd_args[0], ft_strlen(cmd_args[0]));
			write(STDERR_FILENO, ": command not found\n", 20);
			exit(127);
		}
	}
	else
		perror_and_exit(cmd_args[0], EXIT_FAILURE);
}

void	execute_all(t_commands *cmds, t_data *data)
{
	t_process	process;
	pid_t		*pid;
	int			i;
	const int	num_cmd = lst_size(cmds);
	int			pipe_read_end_prev;

	i = -1;
	if (cmds == NULL)
		return ;
	pipe_read_end_prev = dup(STDIN_FILENO);
	if (pipe_read_end_prev == -1)
		return ;
	if (!is_builtin(NULL, cmds->args[0]) || num_cmd > 1)
	{
		pid = malloc(sizeof(pid_t) * num_cmd);
		if (pid == NULL)
			return ;
		while (cmds)
		{
			shell_expansion(cmds->args, data);
			init_process(&process, cmds, pipe_read_end_prev);
			if (process.command != NULL && process.fd_out != -1)
				pid[++i] = create_process(&process);
			if (!process.builtin)
				free(process.cmd_path);
			cmds = cmds->next;
			pipe_read_end_prev = process.pipe_fd[RD];
		}
		wait_process(pid, num_cmd);
		free(pid);
	}
	else
		simple_command(&process, pipe_read_end_prev, cmds, data);
}
