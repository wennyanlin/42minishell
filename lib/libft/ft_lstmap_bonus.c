/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 20:24:44 by wlin              #+#    #+#             */
/*   Updated: 2024/06/22 15:56:02 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result_lst;
	t_list	*new_node;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	result_lst = NULL;
	while (lst)
	{
		content = f(lst->content);
		if (content)
			new_node = ft_lstnew(content);
		if (!content || !new_node)
		{
			free(content);
			ft_lstclear(&result_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&result_lst, new_node);
		lst = lst->next;
	}
	return (result_lst);
}
