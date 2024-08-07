/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:12:32 by rtorrent          #+#    #+#             */
/*   Updated: 2024/08/03 20:24:07 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "macros.h"

static void	quote_removal(char **const args, char **const parg, const char q)
{
	char	*arg_close;
	char	*str1;
	char	*str2;

	*(*parg)++ = '\0';
	arg_close = ft_strchr(*parg, q);
	str1 = ft_substr(*parg, 0, arg_close - *parg);
	str2 = ft_strjoin(*args, str1);
	free(str1);
	str1 = ft_strjoin(str2, ++arg_close);
	if (q == QUOTE_S)
		*parg = str1 + ft_strlen(str2);
	else
		*parg = str1 + ft_strlen(*args);
	free(str2);
	free(*args);
	*args = str1;
}

static void	parameter_expansion(char **const args, char **const parg)
{
	char *const	empty = "";
	char		*arg_param;
	char		*str1;
	char		*str2;
	int			ok_first;

	*(*parg)++ = '\0';
	arg_param = *parg;
	ok_first = (ft_isalpha(**parg) || **parg == UNDERSCORE);
	++*parg;
	while (ok_first && (ft_isalnum(**parg) || **parg == UNDERSCORE))
		++*parg;
	str1 = ft_substr(arg_param, 0, *parg - arg_param);
	arg_param = getenv(str1);
	if (!arg_param)
		arg_param = empty;
	str2 = ft_strjoin(*args, arg_param);
	free(str1);
	str1 = ft_strjoin(str2, *parg);
	*parg = str1 + ft_strlen(str2);
	free(str2);
	free(*args);
	*args = str1;
}

void	shell_expansion(char **args)
{
	char	*arg;

	while (*args)
	{
		arg = *args;
		while (*arg)
		{
			if (*arg == QUOTE_S || *arg == QUOTE_D)
				quote_removal(args, &arg, *arg);
			else if (*arg == DOLLAR)
				parameter_expansion(args, &arg);
			else
				++arg;
		}
		++args;
	}
}
