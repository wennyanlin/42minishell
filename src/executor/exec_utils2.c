/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:46:58 by wlin              #+#    #+#             */
/*   Updated: 2024/08/26 15:19:17 by rtorrent         ###   ########.fr       */
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
	array = NULL;
}

size_t	array_len(char **array)
{
	char **const	array0 = array;

	while (*array)
		array++;
	return (array - array0);
}

int	directory_error(char *cmd)
{
	if (is_equal(".", cmd) == EXIT_SUCCESS)
		return (127);
	if (is_equal("/", cmd) == EXIT_SUCCESS)
		return (126);
	return (0);
}
