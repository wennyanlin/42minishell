/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:12:32 by rtorrent          #+#    #+#             */
/*   Updated: 2024/10/06 23:20:03 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	word_split(char ***pargs, char ***pparg)
{
	char	**split_arg;
	size_t	n;

	split_arg = ft_split(**pparg, UNIT_SEPARATOR);
	free(**pparg);
	*(*pparg)++ = NULL;
	n = array_len(*pargs) + array_len(split_arg);
	array_merge_back(pargs, array_merge_back(&split_arg, *pparg));
	free(split_arg);
	*pparg = *pargs + n - 1;
}

static char	*parameter_expansion(t_data *data, char **args, char **parg,
	int flags)
{
	char	*str1;
	char	*str2;

	if (flags & IQU)
	{
		(*parg)++;
		str1 = ft_itoa(data->exit_status);
	}
	else
	{
		str1 = (*parg)++;
		while (ft_isalnum(**parg) || **parg == UNDERSCORE)
			++*parg;
		str1 = ft_substr(str1, 0, *parg - str1);
		get_value(&str1, flags);
	}
	str2 = *args;
	if (str1)
		str2 = ft_strjoin(str2, str1);
	free(str1);
	return (str2);
}

static void	check_parameter(t_data *data, char **args, char **parg, int flags)
{
	char	*str1;
	char	*str2;

	if (flags & EXP && (*parg)[0] == DOLLAR && (*parg)[1] == QUESTION)
		flags |= IQU;
	else if (!(flags & EXP) || (*parg)[0] != DOLLAR
		|| !(ft_isalpha((*parg)[1]) || (*parg)[1] == UNDERSCORE))
	{
		(*parg)++;
		return ;
	}
	*(*parg)++ = '\0';
	str2 = parameter_expansion(data, args, parg, flags);
	flags &= ~IQU;
	str1 = ft_strjoin(str2, *parg);
	if (str1 && str2)
		*parg = str1 + ft_strlen(str2);
	free(str2);
	free(*args);
	*args = str1;
}

static void	quote_removal(t_data *data, char **args, char **parg, int flags)
{
	const char	quote = **parg;
	char		*arg_close;
	char		*str1;
	char		*str2;

	*(*parg)++ = '\0';
	arg_close = ft_strchr(*parg, quote);
	str1 = ft_substr(*parg, 0, arg_close - *parg);
	str2 = str1;
	if (flags & IDQ)
		while (str2 && *str2)
			check_parameter(data, &str1, &str2, flags);
	str2 = ft_strjoin(*args, str1);
	free(str1);
	str1 = ft_strjoin(str2, ++arg_close);
	if (str1 && str2)
		*parg = str1 + ft_strlen(str2);
	free(str2);
	free(*args);
	*args = str1;
}

void	shell_expansion(t_data *data, char ***pargs, int flags)
{
	char	**args;
	char	*arg;

	if (*pargs == NULL)
		return ;
	args = *pargs;
	while (*args)
	{
		arg = *args;
		while (arg && *arg)
		{
			if (*arg == QUOTE_S)
				flags |= ISQ;
			else if (*arg == QUOTE_D)
				flags |= IDQ;
			if (flags & QRM && flags & (ISQ | IDQ))
				quote_removal(data, args, &arg, flags);
			else
				check_parameter(data, args, &arg, flags);
			flags &= ~(ISQ | IDQ);
		}
		if (flags & WSP && ft_strchr(*args, UNIT_SEPARATOR))
			word_split(pargs, &args);
		++args;
	}
}
