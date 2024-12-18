/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:46:09 by wlin              #+#    #+#             */
/*   Updated: 2024/11/02 12:25:25 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_infile(t_process *process, t_redirect *redirect)
{
	if (close(process->fd_in) == INVALID)
		return (error_message(errno, 3, SHNAME, "close", strerror(errno)));
	process->fd_in = open(redirect->filename, O_RDONLY);
	if (process->fd_in == INVALID)
		return (error_message(errno, 3, SHNAME, redirect->filename,
				strerror(errno)));
	return (OK);
}

static int	redirect_outfile(t_process *process, t_redirect *redirect)
{
	int				flags;
	const mode_t	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

	if (close(process->fd_out) == INVALID)
		return (error_message(errno, 3, SHNAME, "close", strerror(errno)));
	flags = O_CREAT | O_WRONLY;
	if (redirect->type == GREAT)
		flags |= O_TRUNC;
	else if (redirect->type == GREAT_GREAT)
		flags |= O_APPEND;
	process->fd_out = open(redirect->filename, flags, mode);
	if (process->fd_out == INVALID)
		return (error_message(errno, 3, SHNAME, redirect->filename,
				strerror(errno)));
	return (OK);
}

static int	handle_redirection(t_data *data, t_process *process,
	t_redirect *redirect)
{
	char	**redirection_split;

	if (redirect->type == LESS_LESS)
		return (redirect_infile(process, redirect));
	redirection_split = array_dup((char *[2]){redirect->filename, NULL});
	if (redirection_split == NULL)
		return (error_message(errno, 4, SHNAME, "word splitting",
				redirect->filename, strerror(errno)));
	shell_expansion(data, &redirection_split, QRM | EXP | WSP);
	if (array_len(redirection_split) != 1)
	{
		error_message(EXIT_FAILURE, 3, SHNAME, redirect->filename,
			"ambiguous redirect");
		array_clear(&redirection_split);
		return (EXIT_FAILURE);
	}
	free(redirect->filename);
	redirect->filename = redirection_split[0];
	free(redirection_split[1]);
	free(redirection_split);
	if (redirect->type == LESS)
		return (redirect_infile(process, redirect));
	return (redirect_outfile(process, redirect));
}

static int	find_path(t_process *process, char **env, char *cmd)
{
	if (char_index(cmd, SLASH) != NOT_FOUND)
	{
		process->cmd_path = ft_strdup(cmd);
		if (process->cmd_path == NULL)
			return (error_message(errno, 2, SHNAME, strerror(errno)));
	}
	else
	{
		process->cmd_path = find_cmd_path(env, "PATH", cmd);
		if (process->cmd_path == NULL)
			return (error_message(NOTFOUND, 2, cmd, "command not found"));
	}
	return (OK);
}

int	init_process(t_data *data, t_process *process)
{
	t_redirect	*redirect;
	char *const	cmd = process->command->args[0];
	int			hr_code;

	redirect = process->command->redirect;
	while (redirect)
	{
		hr_code = handle_redirection(data, process, redirect);
		if (hr_code != OK)
			return (hr_code);
		redirect = redirect->next;
	}
	if (!is_builtin(&process->builtin, cmd) && cmd)
		return (find_path(process, data->env, cmd));
	return (OK);
}
