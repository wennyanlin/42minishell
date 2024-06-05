/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 15:59:51 by wlin              #+#    #+#             */
/*   Updated: 2023/10/02 15:37:46 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		last_i;
	char	target_char;

	target_char = (char)c;
	i = 0;
	last_i = -1;
	while (s[i] != '\0')
	{
		if (s[i] == target_char)
		{
			last_i = i;
		}
		i++;
	}
	if (target_char == '\0')
		return ((char *)&s[i]);
	else if (last_i >= 0)
		return ((char *)&s[last_i]);
	else
		return (NULL);
}
/*
----
strrchr searches for the last occurrence of target char in s.
-> it iterates through the s and return a pointer to the last occurrance
   of the target char.
-> if the target char is not found, it returns 'NULL'.
-> if the target char is the null terminator, it returns a pointer to the end.
----*//*
#include <stdio.h>
int	main(void)
{
	const char	*s;
	int			c;
	char		*result;

	s = "hello";
	c = 108;
	result = strrchr(s, c);
	printf("%s", result);
	return (0);
}*/
