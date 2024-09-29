/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:12:32 by rtorrent          #+#    #+#             */
/*   Updated: 2024/09/29 21:29:27 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*word_splitting(char **pstr, int in_quote)
{
	char	*value;

	value = *getenv(*pstr);
	if (in_quote)
		return (value);

}

static char	*parameter_expansion(t_data *data, char **args, char **parg,
	const int type)
{
	char	*str1;
	char	*str2;

	str1 = NULL;
	if (type == TILDE)
		str2 = getenv("HOME");
	else if (type == QUESTION)
	{
		(*parg)++;
		str1 = ft_itoa(data->exit_status);
		str2 = str1;
	}
	else
	{
		str2 = (*parg)++;
		while (ft_isalnum(**parg) || **parg == UNDERSCORE)
			++*parg;
		str1 = ft_substr(str2, 0, *parg - str2);
		str2 = word_splitting(&str1, type);
	}
	if (!str2)
		str2 = "";
	str2 = ft_strjoin(*args, str2);
	free(str1);
	return (str2);
}

static void	check_parameter(t_data *data, char **args, char **parg,
	int type)
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
		++args;
	}
}
