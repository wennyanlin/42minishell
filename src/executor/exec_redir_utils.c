/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:46:58 by wlin              #+#    #+#             */
/*   Updated: 2024/08/13 12:48:20 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	directory_error(char *cmd)
{
	if (is_equal(".", cmd) == EXIT_SUCCESS)
		return (127);
	if (is_equal("/", cmd) == EXIT_SUCCESS)
		return (126);
	return (0);
}
