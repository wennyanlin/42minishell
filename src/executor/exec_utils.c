/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:27:19 by wlin              #+#    #+#             */
/*   Updated: 2024/07/27 18:55:34 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "macros.h"
#include "executor.h"

int lst_size(t_commands *cmds)
{
    int             i;
    t_commands		*tmp;
    
    i = 0;
    tmp = cmds;
	while (tmp)
	{
		++i;
		tmp = tmp->next;
	}
    return (i);
}

char	*str_cpy(char *src)
{
	int	i;
	int	src_len;
	char *copy;

	i = -1;
	src_len = str_size(src);
	copy = malloc(sizeof(char) * (src_len + 1));
	if (!copy)
		return (NULL);
	while (src[++i])
		copy[i] = src[i];
	copy[i] = '\0';
	return (copy);
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

int	str_size(const char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return(len);
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