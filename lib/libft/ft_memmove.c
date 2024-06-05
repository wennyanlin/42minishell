/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:10:29 by wlin              #+#    #+#             */
/*   Updated: 2023/10/02 13:08:59 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*p_dst;
	char	*p_src;
	size_t	i;

	p_dst = (char *)dst;
	p_src = (char *)src;
	i = 0;
	if (!p_dst && !p_src)
		return (NULL);
	if (dst > src)
	{
		while (len)
		{
			p_dst[len - 1] = p_src[len - 1];
			len--;
		}
	}
	else
		ft_memcpy(p_dst, p_src, len);
	return (dst);
}
/*
----
memmove safely copies a block of memory from src to dst, preventing data-
corruption in overlapping regions. it suppports both backward and forward
copies and return the dst pointer after completion.
----
#include <stdio.h>

int main()
{
	char dst[] = "hola";
	//char src[] = "adios";
	//size_t len = 3;
	//char dst1[] = "hola";
	ft_memmove(dst + 1, dst, 3);
	printf("ft_memmove(): %s\n", dst);
	//memmove(dst + 1, dst, 3);
	//printf("memmove(): %s\n", dst);
}*/
