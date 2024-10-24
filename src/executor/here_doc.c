/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:15:28 by wlin              #+#    #+#             */
/*   Updated: 2024/10/24 15:00:49 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_read(t_data *dt, char **pwrd, int hd_fd)
{
	const int	quoted = ft_strchr(*pwrd, QUOTE_S) || ft_strchr(*pwrd, QUOTE_D);
	char		**next_line;

	shell_expansion(dt, &pwrd, QRM);
	next_line = (char *[2]){readline(HEREDOC_PROMPT), NULL};
	while (next_line[0] && ft_strncmp(next_line[0], *pwrd, -1))
	{
		if (!quoted)
			shell_expansion(dt, &next_line, EXP);
		ft_putendl_fd(next_line[0], hd_fd);
		free(next_line[0]);
		next_line[0] = readline(HEREDOC_PROMPT);
	}
	free(next_line[0]);
	free(*pwrd);
}

int	heredoc_iter(t_data *data, t_commands *cmd,
	int (*f)(t_data *, char **))
{
	t_redirect	*redirect;
	char		**tmp_array;
	int			return_status;

	if (!cmd)
		return (0);
	redirect = cmd->redirect;
	while (redirect)
	{
		if (redirect->type == LESS_LESS)
		{
			tmp_array = (char *[2]){redirect->filename, NULL};
			return_status = f(data, tmp_array);
			if (return_status != 0)
				return (return_status);
			redirect->filename = tmp_array[0];
		}
		redirect = redirect->next;
	}
	return (heredoc_iter(data, cmd->next, f));
}

t_heredoc	init_heredoc(t_data *dt)
{
	char *const	filename = heredoc_create_filename();
	int			hd_fd;
	pid_t		pid;
	t_heredoc	heredoc;

	if (filename == NULL)
		exit_minishell(dt, errno, 3, SHNAME, "here-document", strerror(errno));
	hd_fd = open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if (hd_fd == INVALID)
		exit_minishell(dt, errno, 3, SHNAME, filename, strerror(errno));
	pid = fork();
	if (pid == INVALID)
		exit_minishell(dt, errno, 3, SHNAME, "fork", strerror(errno));
	heredoc.fd = hd_fd;
	heredoc.pid = pid;
	heredoc.filename = filename;
	return (heredoc);
}

int	heredoc_fork(t_data *data, char **pwrd)
{
	t_heredoc	heredoc;
	int			heredoc_exit;

	heredoc = init_heredoc(data);
	if (heredoc.pid == CHILD)
	{
		set_signal(HEREDOC);
		heredoc_read(data, pwrd, heredoc.fd);
		free(heredoc.filename);
		exit(EXIT_SUCCESS);
	}
	heredoc_exit = wait_process(&heredoc.pid, 1);
	*pwrd = heredoc.filename;
	if (close(heredoc.fd) == INVALID)
		exit_minishell(data, errno, 3, SHNAME, "close", strerror(errno));
	return (heredoc_exit);
}
