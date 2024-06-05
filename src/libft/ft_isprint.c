/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:50:40 by wlin              #+#    #+#             */
/*   Updated: 2023/09/09 13:50:44 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	int	isprint;

	isprint = 0;
	if (' ' <= c && c <= '~')
	{
		isprint = 1;
	}
	return (isprint);
}
/*
int	main(void)
{
	int	c;

	c = 32;
	printf("%i", ft_isprint(c));
} */
