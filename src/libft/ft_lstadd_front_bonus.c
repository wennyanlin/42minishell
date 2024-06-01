/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:58:45 by wlin              #+#    #+#             */
/*   Updated: 2023/10/03 12:00:47 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst)
		*lst = new;
	else
	{
		new->next = *lst;
		(*lst) = new;
	}
}

/*
int	main()
{
	char	*str1   = "Hola";
	char	*str2   = "Buenos";
	char	*str3	= "Dias";
	t_list	*lst 	= NULL;
	t_list	*node_1 = ft_lstnew((char *)str1);
	t_list	*node_2 = ft_lstnew((char *)str2);
	t_list	*node_3 = ft_lstnew((char *)str3);

	ft_lstadd_front(&lst, node_1);
	ft_lstadd_front(&lst, node_2);
	ft_lstadd_front(&lst, node_3);
	//printf("Node %d content: %s\n", 1, node_1->content);
	//printf("Node %d content: %s\n", 2, node_2->content);
	//printf("Node %d content: %s\n", 3, node_3->content);	
	
	while (lst)
	{
		printf("Node %d content: %s\n", 3, (char *)(lst->content));
		lst = lst->next;
	}
	return (0);
}
*/
