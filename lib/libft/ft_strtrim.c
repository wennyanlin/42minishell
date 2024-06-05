/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:40:58 by wlin              #+#    #+#             */
/*   Updated: 2023/10/03 11:44:11 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		s1_len;
	int		i;
	int		j;
	char	*result;
	int		result_len;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	s1_len = ft_strlen(s1);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (s1_len > i && ft_strchr(set, s1[s1_len -1]))
		s1_len--;
	result_len = s1_len - i;
	result = malloc((result_len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	j = 0;
	while (i < s1_len)
		result[j++] = s1[i++];
	result[j] = '\0';
	return (result);
}
/*
#include <stdio.h>
int	main()
{
	char	*s1 = "2345678holaquetal2345678";
	char	*set = "2345678";

	printf("%s", ft_strtrim(s1, set));
	return (0);
}*/
