/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:12:32 by rtorrent          #+#    #+#             */
/*   Updated: 2024/10/17 04:11:54 by rtorrent         ###   ########.fr       */
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
	if (str1)
		str2 = ft_strjoin(*args, str1);
	if (!str1 || !str2)
		str2 = *args;
	free(str1);
	return (str2);
}

static int	check_parameter(t_data *data, char **args, char **parg, int flags)
{
	char	*str1;
	char	*str2;

	if (flags & EXP && (*parg)[0] == DOLLAR && (*parg)[1] == QUESTION)
		flags |= IQU;
	else if (!(flags & EXP) || (*parg)[0] != DOLLAR
		|| !(ft_isalpha((*parg)[1]) || (*parg)[1] == UNDERSCORE))
		return (*(*parg)++);
	*(*parg)++ = '\0';
	str2 = parameter_expansion(data, args, parg, flags);
	flags &= ~IQU;
	str1 = ft_strjoin(str2, *parg);
	if (str1)
		*parg = str1 + ft_strlen(str2);
	else
		*parg = str2 + ft_strlen(str2);
	if (str2 != *args)
		free(str2);
	if (str1)
	{
		free(*args);
		*args = str1;
	}
	return (FALSE);
}

static int	quote_removal(t_data *data, char **args, char **parg, int flags)
{
	const char	quote = **parg;
	char		*arg_close;
	char		*str1;
	char		*str2;

	flags |= INQ;
	*(*parg)++ = '\0';
	arg_close = ft_strchr(*parg, quote);
	str1 = ft_substr(*parg, 0, arg_close - *parg);
	str2 = str1;
	if (quote == QUOTE_D)
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
	return (TRUE);
}

void	shell_expansion(t_data *data, char ***pargs, int flags)
{
	char	**args;
	char	*arg;
	int		explicit_content;

	if (*pargs == NULL)
		return ;
	args = *pargs;
	while (*args)
	{
		explicit_content = FALSE;
		arg = *args;
		while (arg && *arg)
		{
			if (flags & QRM && (*arg == QUOTE_S || *arg == QUOTE_D))
				explicit_content |= quote_removal(data, args, &arg, flags);
			else
				explicit_content |= check_parameter(data, args, &arg, flags);
		}
		if (flags & WSP && (!explicit_content || *args))
			word_split(pargs, &args);
		++args;
	}
}
