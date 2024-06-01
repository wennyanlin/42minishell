/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 20:53:53 by wlin              #+#    #+#             */
/*   Updated: 2023/10/02 17:48:16 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *s, char c)
{
	int	total_words;

	total_words = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != '\0')
			total_words++;
		while (*s != c && *s != '\0')
			s++;
	}
	return (total_words);
}

static char	**free_matrix(char **matrix, size_t array_i)
{
	size_t	i;

	i = 0;
	while (i < array_i)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	start;
	size_t	array_i;
	char	**result;

	result = malloc(sizeof(char *) * (count_words((char *) s, c) + 1));
	if (!result)
		return (NULL);
	i = 0;
	array_i = 0;
	start = 0;
	while (s[i])
	{
		if (i > 0 && s[i] != c && s[i - 1] == c)
			start = i;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			result[array_i++] = ft_substr(s, start, i - start + 1);
			if (!result[array_i - 1])
				return (free_matrix(result, array_i - 1));
		}
		i++;
	}
	result[array_i] = NULL;
	return (result);
}
/*----
1 -> Count words: count one word when first time met a char is difference
     by seperater or '\0', otherwise keep advancing.
2 -> Create the memory space using malloc for the length of words.
3 -> Filing the substring: in a loop when find one word, using substr to put
     in each position in the array.
     - find starting point of one word at the position
       when the current isn't separater but before it is.
	 - find stopping point where the char it's at before the separater of the '\0'.
4 -> Add NULL to the end of the big array.
----*//*
#include <stdio.h>
int	main(int argc, char *argv[])
{
	char str[] = "adios que tal";
	if (argc == 3)
	{
		char **h = ft_split(argv[1], argv[2][0]);
		int i = 0;
		while (h[i])
			printf("%s\n", h[i++]);
		printf("total palabras estatico: %d\n", count_words(str, argv[2][0]));
		printf("total palabras dinamico: %d\n", count_words(argv[1], argv[2][0]));
	}
	return (0);
}*/
