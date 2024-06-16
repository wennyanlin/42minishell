/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:34:51 by wlin              #+#    #+#             */
/*   Updated: 2024/06/16 23:26:47 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "macros.h"

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
	int	j;

	j = 0;
	while (str[i + j] && is_whitespace(str[i + j]))
		j++;
	return (0);
}

int	find_end_chars_index(char *input, int i)
{
	while (!is_whitespace(input[i]))
		i++;
	return (i - 1);
}

int	find_matching_quote(char *input, int i, char quote)
{
	i -= 1;
	while (input[++i])
	{
		if (input[i] == quote)
			return (i);
	}
	return (NOT_FOUND);
}

int	is_delimiter(char c)
{
	if (is_whitespace(c) || c == '|' || c == '<' || c == '>')
		return (TRUE);
	return (FALSE);
}

