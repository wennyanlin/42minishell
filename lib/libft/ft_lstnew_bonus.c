/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokennew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:38:47 by wlin              #+#    #+#             */
/*   Updated: 2023/10/03 12:00:00 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_tokennew(void *content)
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

	t_list	*node_1 = ft_tokennew(&content);
	t_list	*node_2 = ft_tokennew(&content);
	t_list	*node_3 = ft_tokennew(&content);
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
	t_list	*node_1 = ft_tokennew("Hello");
	t_list	*node_2 = ft_tokennew("wat's up");
	t_list *lst;

	lst = node_1;
	node_1->next = node_2;

	while (lst != NULL)
	{
		printf("%c\n", *(char *)(lst->content));
		lst = lst->next;
	}
}*/
