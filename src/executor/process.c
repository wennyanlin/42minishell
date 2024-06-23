/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:16:01 by wlin              #+#    #+#             */
/*   Updated: 2024/06/23 19:13:15 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "macros.h"

void	fd_dup2(int oldfd, int newfd)
{
	if (oldfd != -1 && dup2(oldfd, newfd) == -1)
	{
		close(oldfd);
		perror_and_exit("dup2", EXIT_FAILURE);
	}
	close(oldfd);
}

void	child_process(int pipe_fd[2], t_exec_state *state)
{
    if (access(state->cmd_path, X_OK) == -1
        && access(state->cmd_path, F_OK) == 0)
    {
        write(STDERR_FILENO, state->cmd_args[0], str_size(state->cmd_args[0]));
        write(STDERR_FILENO, ": permission denied\n", 20);
        exit (126);
    }
    if (state->fd_in == -1)
    { 
        close(pipe_fd[WR]);
        close(pipe_fd[RD]);
        exit (127);
    }
    fd_dup2(state->fd_in, STDIN_FILENO);
	close(pipe_fd[RD]);
	fd_dup2(pipe_fd[WR], STDOUT_FILENO);
	execute_command(state->cmd_path, state->cmd_args, state->envp);
	exit(127);
}

void create_process(t_exec_state *state)
{
    int     pipe_fd[2];
    pid_t   pid;

    if (pipe(pipe_fd) == INVALID)
        perror_and_exit("pipe", EXIT_FAILURE);
    pid = fork();
    if (pid == INVALID)
        perror_and_exit("fork", EXIT_FAILURE);
    else if (pid == CHILD)
        child_process(pipe_fd, state);
    // state->pid_arr[state->cmd_idx] = pid;
    close(state->fd_in);
    state->fd_in = pipe_fd[RD];
    close(pipe_fd[WR]);
}