/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 00:52:42 by wlin              #+#    #+#             */
/*   Updated: 2023/09/18 12:30:01 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*result;
	size_t			i;
	unsigned char	*copy;

	result = (unsigned char *)dst;
	i = 0;
	copy = (unsigned char *)src;
	if (!result && !copy)
	{
		return (NULL);
	}
	while (i < n)
	{
		result[i] = copy[i];
		i++;
	}
	return (dst);
}
