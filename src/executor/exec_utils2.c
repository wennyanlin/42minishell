/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:46:58 by wlin              #+#    #+#             */
/*   Updated: 2024/08/28 14:55:07 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

size_t	array_len(char **array)
{
	char **const	array0 = array;

	while (*array)
		array++;
	return (array - array0);
}

char	**array_dup(char **array)
{
	char **const	array0 = malloc((array_len(array) + 1) * sizeof(char *));
	char			**a;

	if (array0)
	{
		a = array0;
		while (*array)
		{
			*a = ft_strdup(*array++);
			if (!*a++)
			{
				free_array(array0);
				return (NULL);
			}
		}
		*a = NULL;
	}
	return (array0);
}

int	directory_error(char *cmd)
{
	if (is_equal(".", cmd) == EXIT_SUCCESS)
		return (127);
	if (is_equal("/", cmd) == EXIT_SUCCESS)
		return (126);
	return (0);
}
