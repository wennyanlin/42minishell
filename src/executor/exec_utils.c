/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:27:19 by wlin              #+#    #+#             */
/*   Updated: 2024/08/19 16:32:08 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lst_size(t_commands *cmds)
{
	int			i;
	t_commands	*tmp;

	i = 0;
	tmp = cmds;
	while (tmp)
	{
		++i;
		tmp = tmp->next;
	}
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

int	is_equal(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2))
	{
		if (ft_strncmp(s1, s2, ft_strlen(s1)) == 0)
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
