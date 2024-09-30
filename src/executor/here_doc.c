/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:15:28 by wlin              #+#    #+#             */
/*   Updated: 2024/09/30 17:15:32 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_heredoc_filename()
{
	return ("/tmp/tmp_heredoc");
}

int	check_limiter(char *next_line, char *limiter)
{
	int	i;

	if ((ft_strlen(next_line)) == ft_strlen(limiter))
	{
		i = -1;
		while (limiter[++i])
			if (next_line[i] != limiter[i])
				return (0);
		return (1);
	}
	return (0);
}

char	*read_here_doc(t_data *data, char *limiter)
{
	char	*next_line;
	char	*filename;
	int		hd_fd;

	filename = create_heredoc_filename();
	hd_fd = open(filename, O_CREAT | O_WRONLY, 0666);
	if (hd_fd == INVALID)
		exit_minishell(data, filename, strerror(errno), errno);
	next_line = readline(HEREDOC_PROMPT);
	while (check_limiter(next_line, limiter) == 0)
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
