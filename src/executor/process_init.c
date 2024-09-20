/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:46:09 by wlin              #+#    #+#             */
/*   Updated: 2024/09/20 13:25:47 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_infile(t_data *data, t_process *process, t_redirect *redirect)
{
	if (close(process->fd_in) == INVALID)
		exit_minishell(data, "close", strerror(errno), errno);
	process->fd_in = open(redirect->filename, O_RDONLY);
	if (process->fd_in == INVALID)
		exit_minishell(data, redirect->filename, strerror(errno), errno);
}

void	redirect_outfile(t_data *data, t_process *process, t_redirect *redirect)
{
	int				flags;
	const mode_t	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

	if (close(process->fd_out) == INVALID)
		exit_minishell(data, "close", strerror(errno), errno);
	flags = O_CREAT | O_WRONLY;
	if (redirect->type == GREAT)
		flags |= O_TRUNC;
	else if (redirect->type == GREAT_GREAT)
		flags |= O_APPEND;
	process->fd_out = open(redirect->filename, flags, mode);
	if (process->fd_out == INVALID)
		exit_minishell(data, redirect->filename, strerror(errno), errno);
}

void	handle_redirection(t_data *data, t_process *process,
	t_redirect *redirect)
{
	char	*args[2];

	args[0] = redirect->filename;
	args[1] = NULL;
	shell_expansion(data, args);
	redirect->filename = args[0];
	if (redirect->type == LESS)
		redirect_infile(data, process, redirect);
	else if (redirect->type == LESS_LESS)
		redirect_infile(data, process, redirect);
	else if (redirect->type == GREAT)
		redirect_outfile(data, process, redirect);
	else if (redirect->type == GREAT_GREAT)
		redirect_outfile(data, process, redirect);
}

void	init_process(t_data *data, t_process *process)
{
	t_redirect	*redirect;

	shell_expansion(data, process->command->args);
	if (process->command->args != NULL
		&& !is_builtin(&process->builtin, process->command->args[0]))
	{
		process->cmd_path = find_cmd_path(data, process->command->args[0]);
		data->cmd_path = process->cmd_path;
	}
	redirect = process->command->redirect;
	while (redirect)
	{
		handle_redirection(data, process, redirect);
		redirect = redirect->next;
	}
}
