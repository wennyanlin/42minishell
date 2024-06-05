/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 17:36:17 by wlin              #+#    #+#             */
/*   Updated: 2023/09/24 18:03:36 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
}
/*
#include <fcntl.h>
int	main()
{
	char *s = "Hello Wen, you are amazing!";
	char *path = "/Users/wlin/Desktop/wen.txt";
	int	fd = open(path, O_RDWR|O_CREAT, 0777);
	if (fd == -1)
	{
		perror("error:");
		return (1);
	}
	ft_putendl_fd(s, fd);
	return (0);
}*/
