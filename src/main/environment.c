/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:50:59 by rtorrent          #+#    #+#             */
/*   Updated: 2024/10/20 14:54:08 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getenvp(char **envp, char *name)
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
