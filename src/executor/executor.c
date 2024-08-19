/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 11:46:39 by wlin              #+#    #+#             */
/*   Updated: 2024/08/19 16:31:05 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	execute_command(char *command_path, char **cmd_args, char **envp)
{
	char	**result_array_concat;

	result_array_concat = NULL;
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
			write(STDERR_FILENO, cmd_args[0], ft_strlen(cmd_args[0]));
			write(STDERR_FILENO, ": command not found\n", 20);
			exit(127);
		}
	}
	else
		perror_and_exit(cmd_args[0], EXIT_FAILURE);
}

char	*execute_all(t_commands *cmds, t_data *data)
{
	t_process		process;
	pid_t			*pid;
	int				i;
	const int		num_cmd = lst_size(cmds);
	int				pipe_read_end_prev;
	char			**envp;

	i = -1;
	pid = malloc(sizeof(pid_t) * num_cmd);
	pipe_read_end_prev = dup(STDIN_FILENO);
	while (cmds)
	{
		if (cmds->args != NULL)
			shell_expansion(cmds->args, data);
		envp = lst_to_array(data->env);
		process = init_process(cmds, envp, get_lst_env(data->env, "PATH"),
				pipe_read_end_prev);
		if (process.command != NULL)
		{
			if (is_builtin(process.command[0]) == 1 && process.fd_out != -1)
				pid[++i] = create_process(&process);
		}
		free_array(envp);
		cmds = cmds->next;
		pipe_read_end_prev = process.pipe_fd[RD];
	}
	wait_process(pid, num_cmd);
	free(pid);
	return (process.cmd_path);
}
