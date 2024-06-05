/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:04:34 by wlin              #+#    #+#             */
/*   Updated: 2023/09/26 15:15:36 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	putnbr_recursive(int n, int fd)
{
	char	digit;

	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		digit = '0' + n % 10;
		write(fd, &digit, 1);
	}
	else if (n < 10)
	{
		digit = '0' + n % 10;
		write(fd, &digit, 1);
	}
	return ;
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	else if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	putnbr_recursive(n, fd);
}
/*
#include <fcntl.h>
int	main()
{
	int	n = -5468;
	char *path = "/Users/wlin/Desktop/fuckrecursive.txt";
	//int fd;
	int fd = open(path, O_RDWR|O_CREAT, 0777);
	if (fd == -1)
	{
		perror("error");
		return (0);
	}
	//fd = 1;
	ft_putnbr_fd(n, fd);
}*/
