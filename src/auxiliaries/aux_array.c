/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:08:04 by rtorrent          #+#    #+#             */
/*   Updated: 2024/08/29 03:12:04 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	array_clear(char ***parray)
{
	char	**a;

	a = *parray;
	if (!*a)
		return ;
	while (*a)
		free(*a++);
	free(*parray);
	*parray = NULL;
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
	char	**a0;
	char	**a;

	a0 = malloc((array_len(array) + 1) * sizeof(char *));
	if (a0)
	{
		a = a0;
		while (*array)
		{
			*a = ft_strdup(*array++);
			if (!*a)
			{
				array_clear(&a0);
				break ;
			}
			a++;
		}
		*a = NULL;
	}
	return (a0);
}

char	**array_add_front(char ***parray, char *str)
{
	char **const	a0 = malloc((array_len(*parray) + 2) * sizeof(char *));
	char			**a;
	char			**array;

	if (a0)
	{
		a = a0;
		*a++ = str;
		array = *parray;
		while (*array)
		{
			*a = *array++;
			a++;
		}
		*a = NULL;
		free(*parray);
		*parray = a0;
	}
	return (a0);
}