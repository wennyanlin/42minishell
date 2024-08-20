/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:15:28 by wlin              #+#    #+#             */
/*   Updated: 2024/08/19 16:31:30 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	read_here_doc(char *limiter)
{
	int		pipe_fd[2];
	char	*next_line;

	pipe(pipe_fd);
	next_line = readline(HEREDOC_PROMPT);
	while (check_limiter(next_line, limiter) == 0)
	{
		write(pipe_fd[WR], next_line, ft_strlen(next_line));
		write(pipe_fd[WR], "\n", 1);
		free(next_line);
		next_line = readline(HEREDOC_PROMPT);
	}
	close(pipe_fd[WR]);
	free(next_line);
	return (pipe_fd[RD]);
}
