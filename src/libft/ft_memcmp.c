/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:33:35 by wlin              #+#    #+#             */
/*   Updated: 2023/10/02 16:08:30 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1 && str2 && i < n && (str1[i] == str2[i]))
		i++;
	if (i < n && str1[i] != str2[i])
		return (str1[i] - str2[i]);
	return (0);
}
/*
----
memcmp compares the initial n bytes of memory blocks pointed to by s1 and s2.
-> returns the difference between the fisrt differing bytes.
-> returns 0 if blocks are identical up to length n.
----*//*
#include <stdio.h>
int	main()
{
	int arr1[] = {1, 2, 3, 4};
	int	arr2[] = {1, 2, 3, 4};

	int	result = ft_memcmp(arr1, arr2, sizeof(arr1));
	printf("%d", result);
	return (0);
}*/
