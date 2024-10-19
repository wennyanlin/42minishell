/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 20:17:10 by rtorrent          #+#    #+#             */
/*   Updated: 2024/10/19 14:27:36 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	mark_spaces(unsigned int i, char c)
{
	(void)i;
	if (!c || !is_whitespace(c))
		return (c);
	return (UNIT_SEPARATOR);
}

static char	*getenvp(char **envp, char *name)
{
	size_t	n;

	if (name)
	{
		n = ft_strlen(name);
		while (*envp)
		{
			if (!ft_strncmp(*envp, name, n) && (*envp)[n] == EQUALS)
				return (*envp + ++n);
			envp++;
		}
	}
	return (NULL);
}

void	get_value(char **envp, char **pstr, unsigned int flags)
{
	char	*value;

	value = getenvp(envp, *pstr);
	if (value)
	{
		if (flags & INQ || !(flags & WSP))
			value = ft_strdup(value);
		else
			value = ft_strmapi(value, mark_spaces);
	}
	free(*pstr);
	*pstr = value;
}
