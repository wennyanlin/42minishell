/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 20:17:37 by rtorrent          #+#    #+#             */
/*   Updated: 2024/08/14 19:07:53 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_lst_env(t_var *content)
{
	free(content->name);
	free(content->value);
	free(content);
}

void	del_data(t_data *data)
{
	free(data->exit_status);
	ft_lstclear(&data->env, (void (*)(void *))del_lst_env);
}

char	**lst_to_array(t_list *lst)
{
	size_t	n;
	char	**a;
	t_var	*content;
	char	*str;

	n = ft_lstsize(lst);
	a = malloc((n + 1) * sizeof(char *));
	a[n] = NULL;
	while (n--)
	{
		content = lst->content;
		a[n] = ft_strdup(content->name);
		str = ft_strjoin(a[n], "=");
		free(a[n]);
		a[n] = ft_strjoin(str, content->value);
		free(str);
		lst = lst->next;
	}
	return (a);
}

char	*get_lst_env(t_list *lst, const char *identifier)
{
	t_var	*content;

	while (lst)
	{
		content = lst->content;
		if (!ft_strncmp(content->name, identifier, -1))
			return (content->value);
		lst = lst->next;
	}
	return (NULL);
}

void	new_lst_env(t_list **plst, char **envp)
{
	t_var	*new;
	size_t	eql_idx;

	*plst = NULL;
	while (*envp)
	{
		new = malloc(sizeof(t_var));
		eql_idx = ft_strchr(*envp, '=') - *envp;
		new->name = ft_substr(*envp, 0, eql_idx);
		new->value = ft_strdup(*envp + eql_idx + 1);
		ft_lstadd_front(plst, ft_lstnew(new));
		envp++;
	}
}
