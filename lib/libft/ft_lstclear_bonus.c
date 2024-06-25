/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:27:04 by wlin              #+#    #+#             */
/*   Updated: 2024/06/22 15:56:02 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cpy;

	if (!lst)
		return ;
	while (*lst)
	{
		cpy = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = cpy;
	}
}
