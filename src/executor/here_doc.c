/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:15:28 by wlin              #+#    #+#             */
/*   Updated: 2024/10/04 22:46:31 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_heredoc_filename(void)
{
	char	*filename_prefix;
	char	*filename_suffix;
	char	*filename;
	int		i;

	filename_prefix = "/tmp/tmp_heredoc";
	filename = ft_strdup(filename_prefix);
	i = 0;
	while (filename != NULL && access(filename, F_OK) == 0)
	{
		free(filename);
		filename_suffix = ft_itoa(i);
		if (filename_suffix == NULL)
			return (NULL);
		filename = ft_strjoin(filename_prefix, filename_suffix);
		free(filename_suffix);
		i++;
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

char	*read_here_doc(t_data *data, char **word)
{
	const int	quoted = ft_strchr(*word, QUOTE_S) || ft_strchr(*word, QUOTE_D);
	char		**next_line;
	char		*filename;
	int			hd_fd;

	filename = create_heredoc_filename();
	if (filename == NULL)
		exit_minishell(data, "here-document", strerror(errno), errno);
	hd_fd = open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if (hd_fd == INVALID)
		exit_minishell(data, filename, strerror(errno), errno);
	shell_expansion(data, &word, QRM);
	next_line = (char *[2]){readline(HEREDOC_PROMPT), NULL};
	while (check_delimiter(next_line[0], word[0]) == 0)
	{
		if (!quoted)
			shell_expansion(data, &next_line, EXP);
		ft_putendl_fd(next_line[0], hd_fd);
		free(next_line[0]);
		next_line[0] = readline(HEREDOC_PROMPT);
	}
	close(hd_fd);
	free(next_line[0]);
	return (filename);
}
