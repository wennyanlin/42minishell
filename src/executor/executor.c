/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 11:46:39 by wlin              #+#    #+#             */
/*   Updated: 2024/09/20 13:28:41 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_command(t_data *data, t_commands *cmd)
{
	t_process	process;

	process.command = cmd;
	process.fd_in = dup(STDIN_FILENO);
	if (process.fd_in == INVALID)
		exit_minishell(data, "dup", strerror(errno), errno);
	process.fd_out = dup(STDOUT_FILENO);
	if (process.fd_out == INVALID)
		exit_minishell(data, "dup", strerror(errno), errno);
	init_process(data, &process);
	data->exit_status = (*process.builtin)(array_len(process.command->args),
			process.command->args, data) & 0377;
	if (close(process.fd_in) == INVALID)
		exit_minishell(data, "close", strerror(errno), errno);
	if (close(process.fd_out) == INVALID)
		exit_minishell(data, "close", strerror(errno), errno);
}

int	wait_process(pid_t *pid_array, int num_cmd)
{
	int	i;
	int	status;
	int	stat_code;

	i = -1;
	while (++i < num_cmd)
		waitpid(pid_array[i], &status, 0);
	stat_code = EXIT_FAILURE;
	if (WIFEXITED(status))
		stat_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		stat_code = FATALSIGNAL + WTERMSIG(status);
	else if (WIFSTOPPED(status))
		stat_code = FATALSIGNAL + WSTOPSIG(status);
	return (stat_code);
}

void	link_command(t_data *data, t_commands *cmds, pid_t *pid,
		int pipe_read_end_prev)
{
	t_process	process;

	if (!cmds)
		return ;
	process.command = cmds;
	process.fd_in = pipe_read_end_prev;
	if (cmds->next)
	{
		if (pipe(process.pipe_fd) == INVALID)
			exit_minishell(data, "pipe", strerror(errno), errno);
		process.fd_out = process.pipe_fd[WR];
	}
	else
	{
		process.fd_out = dup(STDOUT_FILENO);
		if (process.fd_out == INVALID)
			exit_minishell(data, "dup", strerror(errno), errno);
	}
	*pid = create_process(data, &process);
	pipe_read_end_prev = process.pipe_fd[RD];
	free(data->cmd_path);
	data->cmd_path = NULL;
	link_command(data, cmds->next, ++pid, pipe_read_end_prev);
}

void	execute_all(t_data *data, t_commands *cmds)
{
	int	num_cmd;
	int	pipe_read_end_prev;

	if (cmds == NULL)
		return ;
	num_cmd = lst_size(cmds);
	data->pid = malloc(sizeof(pid_t) * num_cmd);
	if (data->pid == NULL)
		exit_minishell(data, "malloc", strerror(errno), errno);
	if (!is_builtin(NULL, cmds->args[0]) || num_cmd > 1)
	{
		pipe_read_end_prev = dup(STDIN_FILENO);
		if (pipe_read_end_prev == INVALID)
			exit_minishell(data, "dup", strerror(errno), errno);
		link_command(data, cmds, data->pid, pipe_read_end_prev);
		data->exit_status = wait_process(data->pid, num_cmd);
	}
	else
		simple_command(data, cmds);
}
