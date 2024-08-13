/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:12:00 by wlin              #+#    #+#             */
/*   Updated: 2024/08/13 12:54:08 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(void)
{
	printf("EXECUTING #echo# BUILTIN FUNCTION.\n");
}

void	ft_cd(void)
{
	printf("EXECUTING #cd# BUILTIN FUNCTION.\n");
}

void	ft_pwd(void)
{
	printf("EXECUTING #pwd# BUILTIN FUNCTION.\n");
}

void	ft_export(void)
{
	printf("EXECUTING #export# BUILTIN FUNCTION.\n");
}

int	is_builtin(char *cmd)
{
	if (is_equal("echo", cmd) == EXIT_SUCCESS)
		ft_echo();
	else if (is_equal("cd", cmd) == EXIT_SUCCESS)
		ft_cd();
	else if (is_equal("pwd", cmd) == EXIT_SUCCESS)
		ft_pwd();
	else if (is_equal("export", cmd) == EXIT_SUCCESS)
		ft_export();
	else if (is_equal("unset", cmd) == EXIT_SUCCESS)
		ft_unset();
	else if (is_equal("env", cmd) == EXIT_SUCCESS)
		ft_env();
	else if (is_equal("exit", cmd) == EXIT_SUCCESS)
		ft_exit();
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
