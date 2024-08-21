/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:46:58 by wlin              #+#    #+#             */
/*   Updated: 2024/08/21 13:26:28 by rtorrent         ###   ########.fr       */
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

int	directory_error(char *cmd)
{
	if (is_equal(".", cmd) == EXIT_SUCCESS)
		return (127);
	if (is_equal("/", cmd) == EXIT_SUCCESS)
		return (126);
	return (0);
}
