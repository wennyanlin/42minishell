/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:38:47 by wlin              #+#    #+#             */
/*   Updated: 2024/06/22 15:56:02 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list) * 1);
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
/*
#include <stdio.h>
int main()
{
	int content = 14566;

	t_list	*node_1 = ft_lstnew(&content);
	t_list	*node_2 = ft_lstnew(&content);
	t_list	*node_3 = ft_lstnew(&content);
	t_list 	*lst;

	lst = node_1;
	node_1->next = node_2;
	node_2->next = node_3;
	
	while (lst != NULL)
	{
		printf("%i\n", *((int *)(lst->content)));
		lst = lst->next;
	}
}
*//*
int main()
{
	t_list	*node_1 = ft_lstnew("Hello");
	t_list	*node_2 = ft_lstnew("wat's up");
	t_list *lst;

	lst = node_1;
	node_1->next = node_2;

	while (lst != NULL)
	{
		printf("%c\n", *(char *)(lst->content));
		lst = lst->next;
	}
}*/
