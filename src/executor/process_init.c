/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:46:09 by wlin              #+#    #+#             */
/*   Updated: 2024/10/06 19:25:50 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_infile(t_data *data, t_process *process,
	t_redirect *redirect)
{
	if (close(process->fd_in) == INVALID)
		exit_minishell(data, "close", strerror(errno), errno);
	process->fd_in = open(redirect->filename, O_RDONLY);
	if (redirect->type == LESS_LESS)
		unlink(redirect->filename);
	if (process->fd_in == INVALID)
		exit_minishell(data, redirect->filename, strerror(errno), errno);
}

static void	redirect_outfile(t_data *data, t_process *process,
	t_redirect *redirect)
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

static void	handle_redirection(t_data *data, t_process *process,
	t_redirect *redirect)
{
	char	**redirection_split;

	redirection_split = array_dup((char *[2]){redirect->filename, NULL});
	if (redirection_split == NULL)
		exit_minishell(data, redirect->filename, strerror(errno), errno);
	if (redirect->type != LESS_LESS)
		shell_expansion(data, &redirection_split, QRM | EXP | WSP);
	else
		read_here_doc(data, redirection_split);
	if (array_len(redirection_split) != 1)
	{
		error_message(TRUE, redirect->filename, "ambiguous redirect",
			EXIT_FAILURE);
		array_clear(&redirection_split);
		exit_minishell(data, NULL, NULL, EXIT_FAILURE);
	}
	redirect->filename = redirection_split[0];
	free(redirection_split[1]);
	free(redirection_split);
	if (redirect->type == LESS || redirect->type == LESS_LESS)
		redirect_infile(data, process, redirect);
	else if (redirect->type == GREAT || redirect->type == GREAT_GREAT)
		redirect_outfile(data, process, redirect);
}

void	init_process(t_data *data, t_process *process)
{
	t_redirect	*redirect;

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
