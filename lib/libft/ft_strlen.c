/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:21:40 by wlin              #+#    #+#             */
/*   Updated: 2024/07/17 17:16:10 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	if (s == NULL)
		return (0);
	while (*s)
	{
		count++;
		s++;
	}
	return (count);
}
/*
int	main(void)
{
	const char	*s = "hola, ciao";

	printf("%zu", ft_strlen(s));
	return (0);
} */
