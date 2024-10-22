/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:50:59 by rtorrent          #+#    #+#             */
/*   Updated: 2024/10/22 03:19:34 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setenvp(char ***penvp, char *var, char *equals)
{
	char			**p;
	const size_t	n = equals - var;

	p = *penvp;
	if (!p)
		return ;
	while (*p)
	{
		if (!ft_strncmp(*p, var, n) && (!(*p)[n] || (*p)[n] == EQUALS))
			break ;
		p++;
	}
	if (*p)
	{
		free(*p);
		*p = ft_strdup(var);
	}
	else
		array_add(penvp, ft_strdup(var), BACK);
}

char	*getenvp(char **envp, char *name)
{
	size_t	n;

	if (name)
	{
		n = ft_strlen(name);
		while (*envp)
		{
			if (!ft_strncmp(*envp, name, n)
				&& (!(*envp)[n] || (*envp)[n] == EQUALS))
				return (*envp + ++n);
			envp++;
		}
	}
	return (NULL);
}

char	**env_array(char **export_vars)
{
	char	**p;

	p = array_dup((char *[1]){NULL});
	while (p && *export_vars)
	{
		if (ft_strchr(*export_vars, EQUALS)
			&& !array_add(&p, *export_vars, BACK))
			array_clear(&p);
		export_vars++;
	}
	return (p);
}
