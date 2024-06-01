/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:07:14 by wlin              #+#    #+#             */
/*   Updated: 2023/09/09 14:07:18 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	unsigned int	isascii;

	isascii = 0;
	if (c >= 0 && c <= 127)
	{
		isascii = 1;
	}
	return (isascii);
}
/*
int	main(void)
{
	int	c;

	c = 0;
	printf("%i", ft_isascii(c));
} */
