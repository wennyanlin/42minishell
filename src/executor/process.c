/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:16:01 by wlin              #+#    #+#             */
/*   Updated: 2024/07/31 17:44:49 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "macros.h"
#include "minishell.h"

void	fd_dup2(int oldfd, int newfd)
{
	if (oldfd != -1 && dup2(oldfd, newfd) == -1)
	{
		close(oldfd);
		perror_and_exit("dup2", EXIT_FAILURE);
	}
	close(oldfd);
}

void	child_process(t_process *process)
{
    
    if (access(process->cmd_path, X_OK) == -1
        && access(process->cmd_path, F_OK) == 0)
    {
        write(STDERR_FILENO, "minishell: permission denied\n", 20);
        printf("a\n");
        write(STDERR_FILENO, process->command[0], str_size(process->command[0]));
        exit (126);
    }
    if (process->fd_in == -1)
        exit (127);
    fd_dup2(process->fd_in, STDIN_FILENO);
    close(process->fd_in); 
    fd_dup2(process->fd_out, STDOUT_FILENO);
    close(process->fd_out);
    close(process->pipe_fd[RD]);
	execute_command(process->cmd_path, process->command, process->envp);
	exit(127);
}

pid_t create_process(t_process *process)
{
    pid_t   pid;
    
    pid = fork();
    if (pid == INVALID)
        perror_and_exit("fork", EXIT_FAILURE);
    else if (pid == CHILD)
        child_process(process);
    close(process->fd_in);
    close(process->fd_out);
    return (pid);
}
