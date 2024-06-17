/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 20:24:44 by wlin              #+#    #+#             */
/*   Updated: 2023/09/28 00:22:28 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_tokenmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result_token;
	t_list	*new_node;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	result_token = NULL;
	while (lst)
	{
		content = f(lst->content);
		if (content)
			new_node = ft_tokennew(content);
		if (!content || !new_node)
		{
			free(content);
			ft_tokenclear(&result_token, del);
			return (NULL);
		}
		ft_tokenadd_back(&result_token, new_node);
		lst = lst->next;
	}
	return (result_token);
}
