/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 21:42:10 by wlin              #+#    #+#             */
/*   Updated: 2023/09/17 23:17:19 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*p == (unsigned char)c)
		{
			return ((void *)p);
		}
		p++;
		i++;
	}
	return (NULL);
}
/*
int	main()
{
	int s[7] = {-49, 49, 1, -1, 0, -2, 2};
	size_t	n = 3;
	int	c = -1;

    printf("%s", (char *)ft_memchr(s, c, n));
    printf("%s", (char *)memchr(s, c, n));
}*/
