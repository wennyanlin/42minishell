/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:09:53 by rtorrent          #+#    #+#             */
/*   Updated: 2024/10/12 20:57:20 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define FLN 01

int	bt_echo(int argc, char *argv[], t_data *data)
{
	int	option_flags;

	(void)argc;
	(void)data;
	option_flags = 0;
	while (++*argv && **argv == MINUS)
	{
		while(++(*argv
