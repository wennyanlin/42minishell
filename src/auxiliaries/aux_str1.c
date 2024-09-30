/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_str1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:34:51 by wlin              #+#    #+#             */
/*   Updated: 2024/09/30 20:16:49 by rtorrent         ###   ########.fr       */
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

int	find_end_chars_index(char *input, int i)
{
	while (!is_whitespace(input[i]))
		i++;
	return (i - 1);
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

int	is_equal(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2))
	{
		if (ft_strncmp(s1, s2, ft_strlen(s1)) == 0)
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
