/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:12:00 by wlin              #+#    #+#             */
/*   Updated: 2024/08/28 12:34:29 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_bfunc *dst, char *cmd)
{
	static const char		*builtin[] = {"env", "pwd", "unset", NULL};
	static const t_bfunc	bt_func[] = {bt_env, bt_pwd, bt_unset, NULL};
	const char				**b;

	b = builtin;
	while (*b)
	{
		if (!ft_strncmp(*b, cmd, -1))
			break ;
		b++;
	}
	if (dst)
		*dst = bt_func[b - builtin];
	return (bt_func[b - builtin] != NULL);
}
