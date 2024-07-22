/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:12:00 by wlin              #+#    #+#             */
/*   Updated: 2024/07/21 14:17:00 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "macros.h"

void	ft_echo()
{
    printf("EXECUTING #echo# BUILTIN FUNCTION.\n");
}
void    ft_cd()
{
    printf("EXECUTING #cd# BUILTIN FUNCTION.\n");
}
void    ft_pwd()
{
    printf("EXECUTING #pwd# BUILTIN FUNCTION.\n");
}

void	ft_export()
{
    printf("EXECUTING #export# BUILTIN FUNCTION.\n");
}

void	ft_unset()
{
    printf("EXECUTING #unset# BUILTIN FUNCTION.\n");
}

void	ft_env()
{
    printf("EXECUTING #env# BUILTIN FUNCTION.\n");
}

void	ft_exit()
{
    printf("EXECUTING #exit# BUILTIN FUNCTION.\n");
}