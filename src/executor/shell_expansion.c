/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:12:32 by rtorrent          #+#    #+#             */
/*   Updated: 2024/09/07 21:02:17 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parameter_expansion(char **args, char **parg, t_data *data, int t)
{
	char	*arg_param;
	char	*str1;
	char	*str2;

	if (t == TILDE)
	{
		str1 = NULL;
		arg_param = getenv("HOME");
	}
	else
		arg_param = (*parg)++;
	if (t == DOLLAR)
	{
		while (ft_isalnum(**parg) || **parg == UNDERSCORE)
			++*parg;
		str1 = ft_substr(arg_param, 0, *parg - arg_param);
		arg_param = getenv(str1);
	}
	else if (t == QUESTION)
	{
		str1 = ft_itoa(data->exit_status);
		arg_param = str1;
	}
	if (!arg_param)
		arg_param = "";
	str2 = ft_strjoin(*args, arg_param);
	free(str1);
	str1 = ft_strjoin(str2, *parg);
	if (str1 && str2)
		*parg = str1 + ft_strlen(str2);
	free(str2);
	free(*args);
	*args = str1;
}

static void	check_parameter(char **args, char **parg, t_data *data)
{
	int	type;

	if ((*parg)[0] == TILDE && (!(*parg)[1] || is_whitespace((*parg)[1])))
		type = TILDE;
	else if ((*parg)[0] == DOLLAR && (*parg)[1] == QUESTION)
		type = QUESTION;
	else if ((*parg)[0] == DOLLAR
		&& (ft_isalpha((*parg)[1]) || (*parg)[1] == UNDERSCORE))
		type = DOLLAR;
	else
	{
		(*parg)++;
		return ;
	}
	*(*parg)++ = '\0';
	parameter_expansion(args, parg, data, type);
}

static void	quote_removal(char **args, char **parg, const char q, t_data *data)
{
	char	*arg_close;
	char	*str1;
	char	*str2;

	*(*parg)++ = '\0';
	arg_close = ft_strchr(*parg, q);
	str1 = ft_substr(*parg, 0, arg_close - *parg);
	str2 = str1;
	while (q == QUOTE_D && str1 && str2 && *str2)
		check_parameter(&str1, &str2, data);
	str2 = ft_strjoin(*args, str1);
	free(str1);
	str1 = ft_strjoin(str2, ++arg_close);
	if (str1 && str2)
		*parg = str1 + ft_strlen(str2);
	free(str2);
	free(*args);
	*args = str1;
}

void	shell_expansion(t_data *data, char **args)
{
	char	*arg;

	if (args == NULL)
		return ;
	while (*args)
	{
		arg = *args;
		while (arg && *arg)
		{
			if (*arg == QUOTE_S || *arg == QUOTE_D)
				quote_removal(args, &arg, *arg, data);
			else
				check_parameter(args, &arg, data);
		}
		++args;
	}
}
