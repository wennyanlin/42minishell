/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:53:31 by wlin              #+#    #+#             */
/*   Updated: 2024/08/13 12:54:01 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(void)
{
	printf("EXECUTING #unset# BUILTIN FUNCTION.\n");
}

void	ft_env(void)
{
	printf("EXECUTING #env# BUILTIN FUNCTION.\n");
}

void	ft_exit(void)
{
	printf("EXECUTING #exit# BUILTIN FUNCTION.\n");
}
