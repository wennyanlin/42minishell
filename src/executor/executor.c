/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 11:46:39 by wlin              #+#    #+#             */
/*   Updated: 2024/11/02 01:33:31 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	simple_command(t_data *data, t_commands *cmd)
{
	t_process	process;
	const int	dup_fd[2] = {dup(STDIN_FILENO), dup(STDOUT_FILENO)};
	int			sc_exit;

	if (dup_fd[RD] == INVALID || dup_fd[WR] == INVALID)
		exit_minishell(data, errno, 3, SHNAME, "dup", strerror(errno));
	process.command = cmd;
	process.fd_in = STDIN_FILENO;
	process.fd_out = STDOUT_FILENO;
	sc_exit = init_process(data, &process);
	if (!sc_exit)
		sc_exit = (*process.builtin)(array_len(process.command->args),
				process.command->args, data);
	fd_dup2(data, dup_fd[RD], STDIN_FILENO);
	fd_dup2(data, dup_fd[WR], STDOUT_FILENO);
	return (sc_exit & 0377);
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
	if (cmds->prev)
		shell_expansion(data, &cmds->args, QRM | EXP | WSP);
	process.command = cmds;
	process.cmd_path = NULL;
	process.fd_in = pipe_read_end_prev;
	if (cmds->next)
	{
		if (pipe(process.pipe_fd) == INVALID)
			exit_minishell(data, errno, 3, SHNAME, "pipe", strerror(errno));
		process.fd_out = process.pipe_fd[WR];
		pipe_read_end_prev = process.pipe_fd[RD];
	}
	else
	{
		process.fd_out = dup(STDOUT_FILENO);
		if (process.fd_out == INVALID)
			exit_minishell(data, errno, 3, SHNAME, "dup", strerror(errno));
	}
	*pid = create_process(data, &process, pipe_read_end_prev);
	link_command(data, cmds->next, ++pid, pipe_read_end_prev);
}

int	execute_all(t_data *data, t_commands *cmds)
{
	int	num_cmd;
	int	pipe_read_end_prev;

	if (cmds == NULL)
		return (data->exit_status);
	num_cmd = lst_size(cmds);
	data->pid = malloc(sizeof(pid_t) * num_cmd);
	data->env = filter_env_array(data->export_vars);
	if (data->pid == NULL || data->env == NULL)
		exit_minishell(data, errno, 2, SHNAME, strerror(errno));
	shell_expansion(data, &cmds->args, QRM | EXP | WSP);
	if (num_cmd > 1 || !is_builtin(NULL, cmds->args[0]))
	{
		pipe_read_end_prev = dup(STDIN_FILENO);
		if (pipe_read_end_prev == INVALID)
			exit_minishell(data, errno, 3, SHNAME, "dup", strerror(errno));
		link_command(data, cmds, data->pid, pipe_read_end_prev);
		return (wait_process(data->pid, num_cmd));
	}
	else
		return (simple_command(data, cmds));
}
