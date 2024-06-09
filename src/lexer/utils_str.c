/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:34:51 by wlin              #+#    #+#             */
/*   Updated: 2024/06/09 23:01:11 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "macros.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c > 8 && c < 14)
		return (TRUE);
	return (FALSE);
}

int	skip_spaces(char *str, int i)
{
	int	j;

	j = 0;
	while (is_whitespace(str[i + j]))
		j++;
	return (0);
}

int	find_end_chars_index(char *input, int i)
{
	while (!is_whitespace(input[i]))
		i++;
	return (i);
}

int	find_matching_quote(char *input, int i, char quote)
{
	int	j;

	j = i - 1;
	while (!is_whitespace(input[++j]))
		if (input[j] == quote)
			return (j);
	if (!input[j] || is_whitespace(input[j]))
		return (NOT_FOUND);
}