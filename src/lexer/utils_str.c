/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:34:51 by wlin              #+#    #+#             */
/*   Updated: 2024/08/19 17:46:40 by wlin             ###   ########.fr       */
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
