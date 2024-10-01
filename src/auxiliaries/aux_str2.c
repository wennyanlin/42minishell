/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_str2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 20:17:10 by rtorrent          #+#    #+#             */
/*   Updated: 2024/10/01 14:15:44 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	mark_spaces(unsigned int i, char *c)
{
	if (*c && is_whitespace(*c))
		*c = UNIT_SEPARATOR;
}
