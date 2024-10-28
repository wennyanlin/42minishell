/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:34:51 by wlin              #+#    #+#             */
/*   Updated: 2024/10/26 01:52:12 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	if (!c)
		return (TRUE);
	if (c == ' ' || (c > 8 && c < 14))
		return (TRUE);
	return (FALSE);
}

int	skip_spaces(char *str, int i)
{
	while (str[i] && is_whitespace(str[i]))
		++i;
	return (i);
}

int	char_index(char *str, char ref)
{
	int	i;

	i = -1;
	if (!str)
		return (-1);
	while (str[++i])
		if (str[i] == ref)
			return (i);
	return (-1);
}

char	*quote_str(char *str)
{
	const size_t	n = ft_strlen(str) + 3;
	char *const		p = malloc(n);

	if (p)
	{
		ft_strlcpy(p, "`", 2);
		ft_strlcat(p, str, n);
		ft_strlcat(p, "\'", n);
	}
	return (p);
}
