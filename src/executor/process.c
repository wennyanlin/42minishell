/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:16:01 by wlin              #+#    #+#             */
/*   Updated: 2024/11/03 00:13:02 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_data *data, char *command_path, char **cmd_args)
{
	struct stat	statbuf;

	if (!stat(command_path, &statbuf))
	{
		if ((statbuf.st_mode & S_IFMT) == S_IFREG)
			execve(command_path, cmd_args, data->env);
		exit_minishell(data, NOTEXECUTABLE, 3, SHNAME, command_path, "Is a directory");
	}
	exit_minishell(data, errno, 3, SHNAME, "stat", strerror(errno));
}

void	child_process(t_data *data, t_process *process)
{
	char *const		cmd_path = process->cmd_path;
	char **const	command = process->command->args;

	fd_dup2(data, process->fd_in, STDIN_FILENO);
	fd_dup2(data, process->fd_out, STDOUT_FILENO);
	if (process->builtin)
		exit((*process->builtin)(array_len(command), command, data));
	if (cmd_path == NULL)
		exit_minishell(data, EXIT_SUCCESS, 0);
	data->cmd_path = cmd_path;
	if (access(cmd_path, F_OK) == INVALID)
		exit_minishell(data, NOTFOUND, 3, SHNAME, command[0],
			"No such file or directory");
	if (access(cmd_path, X_OK) == INVALID)
		exit_minishell(data, NOTEXECUTABLE, 3, SHNAME, command[0],
			"Permission denied");
	execute_command(data, cmd_path, command);
}

pid_t	create_process(t_data *data, t_process *process, int pipe_read_end_prev)
{
	pid_t	pid;
	int		ip_code;

	pid = fork();
	if (pid == INVALID)
		exit_minishell(data, errno, 3, SHNAME, "fork", strerror(errno));
	else if (pid == CHILD)
	{
		set_signal(DEFAULT);
		if (pipe_read_end_prev != process->fd_in
			&& close(pipe_read_end_prev) == INVALID)
			exit_minishell(data, errno, 3, SHNAME, "close", strerror(errno));
		ip_code = init_process(data, process);
		if (ip_code != OK)
			exit_minishell(data, ip_code, 0);
		child_process(data, process);
	}
	if (close(process->fd_in) == INVALID || close(process->fd_out) == INVALID)
		exit_minishell(data, errno, 3, SHNAME, "close", strerror(errno));
	return (pid);
}
