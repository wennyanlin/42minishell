/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:08:04 by rtorrent          #+#    #+#             */
/*   Updated: 2024/10/29 14:29:05 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	array_clear(char ***parray)
{
	char	**a;

	a = *parray;
	if (!a)
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
			if (!*a++)
			{
				array_clear(&a0);
				break ;
			}
		}
		*a = NULL;
	}
	return (a0);
}

char	**array_merge(char ***parray1, char **array2, enum e_location l)
{
	char **const	a0 = malloc((array_len(*parray1) + array_len(array2) + 1)
			* sizeof(char *));
	char			**a;
	char			**array;
	char **const	src[2] = {*parray1, array2};

	if (a0)
	{
		a = a0;
		array = src[0 ^ l];
		while (*array)
			*a++ = *array++;
		array = src[1 ^ l];
		while (*array)
			*a++ = *array++;
		*a = NULL;
		free(*parray1);
		*parray1 = a0;
	}
	return (a0);
}

char	**array_add(char ***parray, char *str, enum e_location l)
{
	if (!*str)
		return (NULL);
	return (array_merge(parray, (char *[2]){str, NULL}, l));
}
