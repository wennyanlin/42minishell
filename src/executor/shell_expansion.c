/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:12:32 by rtorrent          #+#    #+#             */
/*   Updated: 2024/10/02 05:58:08 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	word_split(char ***pargs, char ***pparg)
{
	char	**split_arg;
	size_t	n;

	split_arg = ft_split(**pparg, UNIT_SEPARATOR);
	free(**pparg);
	**pparg++ = NULL;
	n = array_len(*pargs) + array_len(split_arg);
	array_merge(pargs, array_merge(&split_arg, *pparg));
	array_clear(&split_arg);
	*pparg = *pargs + n - 1;
}

static char	*parameter_expansion(t_data *data, char **args, char **parg,
	const int type)
{
	char	*str1;
	char	*str2;

	if (type == TILDE)
		str1 = ft_strdup(getenv("HOME"));
	else if (type == QUESTION)
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
		get_value(&str1, type);
	}
	str2 = *args;
	if (str1)
		str2 = ft_strjoin(str2, str1);
	free(str1);
	return (str2);
}

static void	check_parameter(t_data *data, char **args, char **parg, int type)
{
	char	*str1;
	char	*str2;

	if ((*parg)[0] == TILDE && (!(*parg)[1] || is_whitespace((*parg)[1])))
		type = TILDE;
	else if ((*parg)[0] == DOLLAR && (*parg)[1] == QUESTION)
		type = QUESTION;
	else if ((*parg)[0] != DOLLAR
		|| !(ft_isalpha((*parg)[1]) || (*parg)[1] == UNDERSCORE))
	{
		(*parg)++;
		return ;
	}
	*(*parg)++ = '\0';
	str2 = parameter_expansion(data, args, parg, type);
	str1 = ft_strjoin(str2, *parg);
	if (str1 && str2)
		*parg = str1 + ft_strlen(str2);
	free(str2);
	free(*args);
	*args = str1;
}

static void	quote_removal(t_data *data, char **args, char **parg,
	const char quote)
{
	char	*arg_close;
	char	*str1;
	char	*str2;

	*(*parg)++ = '\0';
	arg_close = ft_strchr(*parg, q);
	str1 = ft_substr(*parg, 0, arg_close - *parg);
	str2 = str1;
	while (quote == QUOTE_D && str1 && str2 && *str2)
		check_parameter(data, &str1, &str2, TRUE);
	str2 = ft_strjoin(*args, str1);
	free(str1);
	str1 = ft_strjoin(str2, ++arg_close);
	if (str1 && str2)
		*parg = str1 + ft_strlen(str2);
	free(str2);
	free(*args);
	*args = str1;
}

void	shell_expansion(t_data *data, char ***pargs)
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
			if (*arg == QUOTE_S || *arg == QUOTE_D)
				quote_removal(data, args, &arg, *arg);
			else
				check_parameter(data, args, &arg, FALSE);
		}
		if (ft_strchr(*args, UNIT_SEPARATOR))
			word_split(pargs, &args);
		++args;
	}
}
