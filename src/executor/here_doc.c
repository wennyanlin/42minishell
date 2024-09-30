/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:15:28 by wlin              #+#    #+#             */
/*   Updated: 2024/09/30 18:12:11 by wlin             ###   ########.fr       */
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

char	*read_here_doc(t_data *data, char *delimiter)
{
	char	*next_line;
	char	*filename;
	int		hd_fd;

	filename = create_heredoc_filename();
	if (filename == NULL)
		exit_minishell(data, "heredoc", strerror(errno), errno);
	hd_fd = open(filename, O_CREAT | O_WRONLY, 0666);
	if (hd_fd == INVALID)
		exit_minishell(data, filename, strerror(errno), errno);
	next_line = readline(HEREDOC_PROMPT);
	while (check_delimiter(next_line, delimiter) == 0)
	{
		write(hd_fd, next_line, ft_strlen(next_line));
		write(hd_fd, "\n", 1);
		free(next_line);
		next_line = readline(HEREDOC_PROMPT);
	}
	close(hd_fd);
	free(next_line);
	return (filename);
}
