/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:46:09 by wlin              #+#    #+#             */
/*   Updated: 2024/08/12 16:57:55 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_error_handling(char *filename, int fd_in)
{
	if ((errno == ENOENT || errno == EACCES)&& fd_in == INVALID)
	{
		printf("%s: %s\n", filename, strerror(errno));
		return (TRUE);
	}
	return (FALSE);
}

int	handle_redirection(t_process *process, t_redirect *redirect)
{
	if (redirect->type == LESS)
	{
		close(process->fd_in);
		process->fd_in = open(redirect->filename, O_RDONLY);
		if (redirection_error_handling(redirect->filename, process->fd_in))
			return (INVALID);
	}
	else if (redirect->type == LESS_LESS)
	{
		close(process->fd_in);
		process->fd_in = read_here_doc(redirect->filename);
		if (redirection_error_handling(redirect->filename, process->fd_in))
			return (INVALID);
	}
	else if (redirect->type == GREAT)
	{
		close(process->fd_out);
		process->fd_out = open(redirect->filename, O_CREAT | O_TRUNC
			| O_RDWR, 00400 | 00200 | 00040 | 00004);
		if (redirection_error_handling(redirect->filename, process->fd_out))
			return (INVALID);
	}
	else if (redirect->type == GREAT_GREAT)
	{
		close(process->fd_out);
		process->fd_out = open(redirect->filename, O_CREAT | O_APPEND
			| O_RDWR, 00400 | 00200 | 00040 | 00004);
		if (redirection_error_handling(redirect->filename, process->fd_out))
			return (INVALID);
	}
	return (TRUE);
}

t_process	init_process(t_commands *cmds, char **envp, int pipe_read_end_prev)
{
	t_process	process;
	t_redirect	*tmp_redirect;

	tmp_redirect = cmds->redirect;
	process.envp = envp;
	process.command = cmds->args;
	if (process.command != NULL)
		process.cmd_path = find_cmd_path(getenv("PATH"), process.command[0]);
	process.fd_in = pipe_read_end_prev;
	if (cmds->next)
	{
		if (pipe(process.pipe_fd) == INVALID)
        	perror_and_exit("pipe", EXIT_FAILURE);
		process.fd_out = process.pipe_fd[WR];
	}
	else
		process.fd_out = dup(STDOUT_FILENO);
	while (tmp_redirect)
	{
		if (handle_redirection(&process, tmp_redirect) == INVALID)
			break;
		tmp_redirect = tmp_redirect->next;
	}
	return (process);
}
