/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 00:28:45 by wlin              #+#    #+#             */
/*   Updated: 2024/10/22 00:35:04 by wlin             ###   ########.fr       */
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

char	*heredoc_create_filename(void)
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