/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:02:02 by wlin              #+#    #+#             */
/*   Updated: 2023/10/02 15:48:53 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/*
----
strncmp compares the first n char of s1 and s2. It uses ASCII values,
stops after n char or at the end, then return the ASCII defference or 0.
-> s1[n] = s2[n] => '0'
-> s1[n] < s2[n] => negative value
-> s1[n] > s2[n] => positive value
----*//*
#include <stdio.h>
int	main()
{
	char *s1 = "Hello";
	char *s2 = "Hola";
	size_t n = 3;
	printf("%i", ft_strncmp(s1, s2, n));
	return (0);
}*/
