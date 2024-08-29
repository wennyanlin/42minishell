/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:34:51 by wlin              #+#    #+#             */
/*   Updated: 2024/08/28 20:31:56 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
