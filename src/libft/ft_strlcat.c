/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:51:27 by wlin              #+#    #+#             */
/*   Updated: 2023/10/02 14:44:55 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	c;

	c = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (dstsize < dest_len)
		return (src_len + dstsize);
	if (dest_len < dstsize - 1 && dstsize > 0)
	{
		while (src[c] && dest_len + c < dstsize - 1)
		{
			dest[dest_len + c] = src[c];
			c++;
		}
		dest[dest_len + c] = '\0';
	}
	return (src_len + dest_len);
}

/*
----
strlcat concatenates strings safely, avoiding buffer overflows. 
-> It calculates the lengths of the dest and sce, 
   then returns if the dest_len is insufficient. 
-> In the concatenation loop, it copies chars from the src to the dest
   until the null terminator or the available space is exhausted.
----*//*
#include <stdio.h>
int	main()
{
	size_t dstsize = 8;
	char *src = "789";
	char dest[20] = "12345678";
	printf("%zu\n", ft_strlcat(dest, src, dstsize));
	//printf("%zu\n", strlcat(dest, src, dstsize));
	printf("%s\n", dest);
	return (0);
}*/
