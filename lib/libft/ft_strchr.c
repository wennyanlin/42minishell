/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:59:12 by wlin              #+#    #+#             */
/*   Updated: 2023/10/02 12:26:34 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	target_char;

	target_char = c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == target_char)
			return ((char *)&s[i]);
		i++;
	}
	if (target_char == '\0')
		return ((char *)s + i);
	return (NULL);
}
/*
----
strchr locates the first occurrence of target character in a giving string,
-> if found, it returns a pointer to that location;
-> if target char. is null-terminator and not found, it returns a pointer to
   the end of the string;
-> if the target char. is not present, it returns 'NULL'.
----
#include <stdio.h>
int	main ()
{
	char s[] = "hello";
	int	c = 108;
	printf("%s", ft_strchr(s, c));
	return (0);
}
*/
