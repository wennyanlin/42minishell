/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 20:37:30 by wlin              #+#    #+#             */
/*   Updated: 2023/09/24 16:35:45 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
#include <fcntl.h>
int main()
{
	char 	*path = "/Users/wlin/Desktop/hola.txt";
	int		fd;

	fd = open(path, O_CREAT|O_RDWR ,0777);
	ft_putchar_fd('w', fd);
}*/
