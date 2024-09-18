/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 11:46:39 by wlin              #+#    #+#             */
/*   Updated: 2024/09/18 19:26:06 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_command(t_data *data, t_process *process, int pipe_read_end_prev)
{
	int	fd_storage[2];

	shell_expansion(data, data->cmds->args);
	init_process(data, data->cmds, process, pipe_read_end_prev);
	if (process->command != NULL && process->fd_out != -1)
	{
		fd_storage[RD] = dup(STDIN_FILENO);
		if (fd_storage[RD] == INVALID)
			exit_minishell(data, "dup", strerror(errno), errno);
		fd_storage[WR] = dup(STDOUT_FILENO);
		if (fd_storage[WR] == INVALID)
			exit_minishell(data, "dup", strerror(errno), errno);
		fd_dup2(data, process->fd_in, STDIN_FILENO);
		fd_dup2(data, process->fd_out, STDOUT_FILENO);
		data->exit_status = (*process->builtin)(array_len(process->command),
				process->command, data) & 0377;
		fd_dup2(data, fd_storage[RD], STDIN_FILENO);
		fd_dup2(data, fd_storage[WR], STDOUT_FILENO);
	}
}

int	get_wait_status(int status)
{
	int	stat_code;

	stat_code = EXIT_FAILURE;
	if (WIFEXITED(status))
		stat_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		stat_code = FATALSIGNAL + WTERMSIG(status);
	else if (WIFSTOPPED(status))
		stat_code = FATALSIGNAL + WSTOPSIG(status);
	return (stat_code);
}

int	wait_process(pid_t *pid_array, int num_cmd)
{
	int	i;
	int	status;

	i = -1;
	while (++i < num_cmd)
		waitpid(pid_array[i], &status, 0);
	return (get_wait_status(status));
}

void	execute_command(t_data *data, char *command_path, char **cmd_args)
{
	char	*shell_path;

	execve(command_path, cmd_args, environ);
	if (errno == ENOEXEC)
	{
		shell_path = getenv("SHELL");
		execve(shell_path, array_add_front(&cmd_args, shell_path), environ);
	}
	else if (errno == ENOENT && char_index(cmd_args[0], '/') == INVALID)
		exit_minishell(data, cmd_args[0], "command not found", NOTFOUND);
	else
		exit_minishell(data, cmd_args[0], strerror(errno), NOTFOUND);
}

void	execute_all(t_data *data, t_commands *cmds)
{
	t_process	process;
	int			i;
	int			num_cmd;
	int			pipe_read_end_prev;

	i = -1;
	if (cmds == NULL)
		return ;
	pipe_read_end_prev = dup(STDIN_FILENO);
	if (pipe_read_end_prev == INVALID)
		exit_minishell(data, "dup", strerror(errno), errno);
	num_cmd = lst_size(cmds);
	data->pid = malloc(sizeof(pid_t) * num_cmd);
	if (data->pid == NULL)
		exit_minishell(data, "malloc", strerror(errno), errno);
	if (!is_builtin(NULL, cmds->args[0]) || num_cmd > 1)
	{
		while (cmds)
		{
			data->pid[++i] = create_process(data, cmds, &process,
					pipe_read_end_prev);
			if (!process.builtin)
				free(process.cmd_path);
			pipe_read_end_prev = process.pipe_fd[RD];
			data->cmd_path = NULL;
			cmds = cmds->next;
		}
		data->exit_status = wait_process(data->pid, num_cmd);
	}
	else
		simple_command(data, &process, pipe_read_end_prev);
}
