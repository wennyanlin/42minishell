/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:16:01 by wlin              #+#    #+#             */
/*   Updated: 2024/09/18 19:24:00 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_data *data, t_process *process)
{
	char *const		cmd_path = process->cmd_path;
	char **const	command = process->command;

	fd_dup2(data, process->fd_in, STDIN_FILENO);
	fd_dup2(data, process->fd_out, STDOUT_FILENO);
	close(process->pipe_fd[RD]);
	if (process->builtin)
		exit((*process->builtin)(array_len(command), command, data));
	if (access(cmd_path, X_OK) == INVALID)
		exit_minishell(data, command[0], "Permission denied", NOTEXECUTABLE);
	execute_command(data, cmd_path, command);
}

pid_t	create_process(t_data *data, t_commands *cmds, t_process *process,
	int pipe_read_end_prev)
{
	pid_t	pid;

	pid = fork();
	if (pid == INVALID)
		exit_minishell(data, "fork", strerror(errno), errno);
	else if (pid == CHILD)
	{
		shell_expansion(data, cmds->args);
		init_process(data, cmds, process, pipe_read_end_prev);
		if (process->command != NULL && process->fd_out != INVALID
			&& process->fd_in != INVALID)
			child_process(data, process);
	}
	close(process->fd_in);
	close(process->fd_out);
	return (pid);
}
