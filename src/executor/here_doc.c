/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:15:28 by wlin              #+#    #+#             */
/*   Updated: 2024/10/21 23:26:06 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_unlink(t_data *data, char **pfilename)
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
	return (0);
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

void	heredoc_read(t_data *dt, char **pwrd, int hd_fd)
{
	const int	quoted = ft_strchr(*pwrd, QUOTE_S) || ft_strchr(*pwrd, QUOTE_D);
	// char *const	filename = heredoc_create_filename();
	// int			hd_fd;
	char		**next_line;
	extern int 	g_sigstatus;

	// if (filename == NULL)
	// 	exit_minishell(dt, errno, 3, SHNAME, "here-document", strerror(errno));
	// hd_fd = open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	// if (hd_fd == INVALID)
	// 	exit_minishell(dt, errno, 3, SHNAME, filename, strerror(errno));
	shell_expansion(dt, &pwrd, QRM);
	next_line = (char *[2]){readline(HEREDOC_PROMPT), NULL};
	while (next_line[0] && ft_strncmp(next_line[0], *pwrd, -1) && g_sigstatus != SIGINT_CODE)
	{
		if (!quoted)
			shell_expansion(dt, &next_line, EXP);
		ft_putendl_fd(next_line[0], hd_fd);
		free(next_line[0]);
		next_line[0] = readline(HEREDOC_PROMPT);
	}
	free(next_line[0]);
	free(*pwrd);
	// *pwrd = filename;
	// if (close(hd_fd) == INVALID)
	// 	exit_minishell(dt, errno, 3, SHNAME, "close", strerror(errno));
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
			printf("filename = %s\n", redirect->filename);
		}
		redirect = redirect->next;
	}
	return (heredoc_iter(data, cmd->next, f));
}

int	heredoc(t_data *dt, char **pwrd)
{
	pid_t		pid;
	int			return_pid;
	extern int	g_sigstatus;
	char *const	filename = heredoc_create_filename();
	int			hd_fd;

	printf("filename create: %s\n", filename);
	if (filename == NULL)
		exit_minishell(dt, errno, 3, SHNAME, "here-document", strerror(errno));
	hd_fd = open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if (hd_fd == INVALID)
		exit_minishell(dt, errno, 3, SHNAME, filename, strerror(errno));
	pid = fork();
	if (pid == INVALID)
		exit_minishell(dt, errno, 3, SHNAME, "fork", strerror(errno));
	else if (pid == CHILD)
	{
		heredoc_read(dt, pwrd, hd_fd);
		exit(0);
	}
	waitpid(pid, &return_pid, 0);
	printf("return_pid = %d, filename %s\n", return_pid, filename);
	*pwrd = filename;
	if (close(hd_fd) == INVALID)
		exit_minishell(dt, errno, 3, SHNAME, "close", strerror(errno));
	if (g_sigstatus == SIGINT_CODE)
		return (SIGINT_CODE);
	else if (return_pid == 0)
		return (0);
	else
		return (exit_minishell(dt, errno, return_pid, SHNAME, "heredoc", strerror(errno)), 0);
}
