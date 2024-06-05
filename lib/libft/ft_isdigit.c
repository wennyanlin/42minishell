/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:41:43 by wlin              #+#    #+#             */
/*   Updated: 2023/09/09 13:42:27 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	int	isdigit;

	isdigit = 0;
	if ('0' <= c && c <= '9')
	{
		isdigit = 1;
	}
	return (isdigit);
}
/*
int main()
{
    int c;

    c = 51;
    printf("%i", isdigit(c));
} */
