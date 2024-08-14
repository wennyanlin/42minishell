/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 20:17:37 by rtorrent          #+#    #+#             */
/*   Updated: 2024/08/14 05:51:46 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lst_to_array(t_list *lst)
{
	size_t	n;
	char	**a;

	n = ft_lstsize(lst);
	a = malloc((n + 1) * sizeof(char *));
	a[n] = NULL;
	while (n--)
	{
		a[n] = ft_strdup(lst->content);
		lst = lst->next;
	}
	return (a);
}

char	*get_lst_env(t_list *lst, const char *identifier)
{
	const size_t	n = ft_strlen(identifier);

	while (lst)
	{
		if (!ft_strncmp(lst->content, identifier, n)
			&& ((char *)lst->content)[n] == '=')
			return ((char *)lst->content + n + 1);
		lst = lst->next;
	}
	return (NULL);
}

void	new_lst_env(t_list **plst, char **envp)
{
	while (*envp)
		ft_lstadd_front(plst, ft_lstnew(*envp++));
}
