/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 22:32:50 by wlin              #+#    #+#             */
/*   Updated: 2023/10/02 18:07:55 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		k = i;
		j = 0;
		while (needle[j] && haystack[k] == needle[j] && k < len)
		{
			k++;
			j++;
		}
		if (needle[j] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
/*----
strnstr locates the first occurence of a needle in haystack within len length.
it uses nested loops to iterate through the strings and compare substrings.
-> returns a pointer to the beginning of the first match.
-> return NULL if no match is found within the len length.
----*//*
#include <stdio.h>
int	main()
{
	char haystack[] = "a squerrel is on top the fridge drinking coke.";
	char needle[] = "squerrel";
	printf("%s", ft_strnstr(haystack, needle, 15));
}*/
