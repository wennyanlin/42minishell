/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:30:30 by wlin              #+#    #+#             */
/*   Updated: 2024/08/14 04:20:44 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	calculate_digits(int n)
{
	int	digits;

	digits = 0;
	while (n != '\0')
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_caso_zero(char n)
{
	char	*result;

	result = (char *)malloc(sizeof(char) * 2);
	if (result == NULL)
		return (NULL);
	result[0] = n;
	result[1] = '\0';
	return (result);
}

int	ft_is_negative(int *n)
{
	int	neg;

	neg = 0;
	if (*n < 0)
	{
		neg = 1;
		*n = *n * -1;
	}
	return (neg);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*result;
	int		digits;
	int		is_negative;

	if (n == 0)
		return (ft_caso_zero('0'));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	digits = calculate_digits(n);
	is_negative = ft_is_negative(&n);
	result = (char *)malloc(digits + is_negative + 1);
	if (result == NULL)
		return (NULL);
	i = digits + is_negative - 1;
	while (n != 0)
	{
		result[i--] = '0' + (n % 10);
		n /= 10;
	}
	if (is_negative)
		result[0] = '-';
	result[digits + is_negative] = '\0';
	return (result);
}

// #include <stdio.h>
// int	main()
// {
// 	printf("%s", ft_itoa(-564));
// 	return (0);
// }
