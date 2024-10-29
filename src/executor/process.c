/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:16:01 by wlin              #+#    #+#             */
/*   Updated: 2024/10/29 12:19:00 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_data *data, char *command_path, char **cmd_args)
{
	char	*shell_path;
	int		e;

	execve(command_path, cmd_args, data->env);
	shell_path = get_from_env(data->env, "SHELL");
	if (shell_path)
	{
		e = errno;
		execve(shell_path, array_add(&cmd_args, shell_path, FRONT), data->env);
		exit_minishell(data, e, 3, SHNAME, cmd_args[1], strerror(e));
	}
	exit_minishell(data, errno, 3, SHNAME, cmd_args[0], strerror(errno));
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
	if (access(cmd_path, F_OK) == INVALID)
		exit_minishell(data, NOTFOUND, 3, SHNAME, command[0],
			"No such file or directory");
	if (access(cmd_path, X_OK) == INVALID)
		exit_minishell(data, NOTEXECUTABLE, 3, SHNAME, command[0],
			"Permission denied");
	execute_command(data, cmd_path, command);
}

pid_t	create_process(t_data *data, t_process *process)
{
	pid_t	pid;

	pid = fork();
	if (pid == INVALID)
		exit_minishell(data, errno, 3, SHNAME, "fork", strerror(errno));
	else if (pid == CHILD)
	{
		set_signal(DEFAULT);
		init_process(data, process);
		child_process(data, process);
	}
	if (close(process->fd_in) == INVALID || close(process->fd_out) == INVALID)
		exit_minishell(data, errno, 3, SHNAME, "close", strerror(errno));
	return (pid);
}
