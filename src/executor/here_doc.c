/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:15:28 by wlin              #+#    #+#             */
/*   Updated: 2024/10/07 20:19:55 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_heredoc_filename(void)
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

int	check_delimiter(char *next_line, char *delimiter)
{
	int	i;

	if ((ft_strlen(next_line)) == ft_strlen(delimiter))
	{
		i = -1;
		while (delimiter[++i])
			if (next_line[i] != delimiter[i])
				return (0);
		return (1);
	}
	return (0);
}

void	read_here_doc(t_data *dt, char **word)
{
	const int	quoted = ft_strchr(*word, QUOTE_S) || ft_strchr(*word, QUOTE_D);
	char *const	filename = create_heredoc_filename();
	int			hd_fd;
	char		**next_line;

	if (filename == NULL)
		exit_minishell(dt, errno, 3, SHNAME, "here-document", strerror(errno));
	hd_fd = open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if (hd_fd == INVALID)
		exit_minishell(dt, errno, 3, SHNAME, filename, strerror(errno));
	shell_expansion(dt, &word, QRM);
	next_line = (char *[2]){readline(HEREDOC_PROMPT), NULL};
	while (next_line[0] && check_delimiter(next_line[0], word[0]) == 0)
	{
		if (!quoted)
			shell_expansion(dt, &next_line, EXP);
		ft_putendl_fd(next_line[0], hd_fd);
		free(next_line[0]);
		next_line[0] = readline(HEREDOC_PROMPT);
	}
	free(next_line[0]);
	free(word[0]);
	word[0] = filename;
	if (close(hd_fd) == INVALID)
		exit_minishell(dt, errno, 3, SHNAME, "close", strerror(errno));
}
