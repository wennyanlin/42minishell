/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 17:06:24 by wlin              #+#    #+#             */
/*   Updated: 2024/11/05 16:05:06 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
/*
#include <fcntl.h>
int	main()
{
	char *s = "hola, que tal";
	char *path = "/Users/wlin/Desktop/putstr.txt";
	int	fd = open(path, O_RDWR|O_CREAT, 0777);
	if (fd == -1)
	{
		perror("error:");
		return (1);
	}
	ft_putstr_fd(s, fd);
	return (0);
}*/
