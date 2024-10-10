/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:15:28 by wlin              #+#    #+#             */
/*   Updated: 2024/10/09 16:49:51 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_unlink(t_data *data, char **pfilename)
{
	const size_t	n = ft_strlen(HEREDOC_PREFIX);

	(void)data;
	if (ft_strncmp(*pfilename, HEREDOC_PREFIX, n) == 0
		&& access(*pfilename, F_OK) == 0)
	{
		if (unlink(*pfilename) == INVALID)
			error_message(errno, 4, SHNAME, "here-document", *pfilename,
				strerror(errno));
		free(*pfilename);
		*pfilename = NULL;
	}
}

static char	*heredoc_create_filename(void)
{
	char	*filename_suffix;
	char	*filename;
	int		i;

	i = 0;
	filename = ft_strjoin(HEREDOC_PREFIX, "0");
	while (filename != NULL && access(filename, F_OK) == 0)
	{
		free(filename);
		filename_suffix = ft_itoa(++i);
		if (filename_suffix == NULL)
			return (NULL);
		filename = ft_strjoin(HEREDOC_PREFIX, filename_suffix);
		free(filename_suffix);
	}
	return (filename);
}

void	heredoc_read(t_data *dt, char **pwrd)
{
	const int	quoted = ft_strchr(*pwrd, QUOTE_S) || ft_strchr(*pwrd, QUOTE_D);
	char *const	filename = heredoc_create_filename();
	int			hd_fd;
	char		**next_line;

	if (filename == NULL)
		exit_minishell(dt, errno, 3, SHNAME, "here-document", strerror(errno));
	hd_fd = open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if (hd_fd == INVALID)
		exit_minishell(dt, errno, 3, SHNAME, filename, strerror(errno));
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
	*pwrd = filename;
	if (close(hd_fd) == INVALID)
		exit_minishell(dt, errno, 3, SHNAME, "close", strerror(errno));
}

void	heredoc_iter(t_data *data, t_commands *cmd,
	void (*f)(t_data *, char **))
{
	t_redirect	*redirect;
	char		**tmp_array;

	if (!cmd)
		return ;
	redirect = cmd->redirect;
	while (redirect)
	{
		if (redirect->type == LESS_LESS)
		{
			tmp_array = (char *[2]){redirect->filename, NULL};
			f(data, tmp_array);
			redirect->filename = tmp_array[0];
		}
		redirect = redirect->next;
	}
	heredoc_iter(data, cmd->next, f);
}
