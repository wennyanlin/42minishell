/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:38:36 by rtorrent          #+#    #+#             */
/*   Updated: 2024/10/07 20:51:36 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	verror_message(int n, va_list *pap)
{
	while (n--)
	{
		ft_putstr_fd(va_arg(*pap, char *), STDERR_FILENO);
		if (n)
			ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
}

int	error_message(int code, int n, ...)
{
	va_list	ap;

	va_start(ap, n);
	if (n)
		verror_message(n, &ap);
	va_end(ap);
	return (code);
}

void	exit_minishell(t_data *data, int code, int n, ...)
{
	va_list	ap;

	va_start(ap, n);
	if (n)
		verror_message(n, &ap);
	va_end(ap);
	clear_data(data);
	array_clear(&data->envp);
	exit(code);
}
