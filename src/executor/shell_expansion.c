/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:12:32 by rtorrent          #+#    #+#             */
/*   Updated: 2024/09/02 03:38:04 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_parameter(char *arg)
{
	return (*arg++ == DOLLAR && (*arg == QUESTION
			|| ft_isalpha(*arg) || *arg == UNDERSCORE));
}

static void	parameter_expansion(char **args, char **parg, t_data *data)
{
	char	*arg_param;
	char	*str1;
	char	*str2;

	*(*parg)++ = '\0';
	arg_param = (*parg)++;
	if (*arg_param != QUESTION)
	{
		while (ft_isalnum(**parg) || **parg == UNDERSCORE)
			++*parg;
		str1 = ft_substr(arg_param, 0, *parg - arg_param);
		arg_param = getenv(str1);
		if (!arg_param)
			arg_param = "";
		free(str1);
	}
	else
		arg_param = data->exit_status;
	str2 = ft_strjoin(*args, arg_param);
	str1 = ft_strjoin(str2, *parg);
	if (str1 && str2)
		*parg = str1 + ft_strlen(str2);
	free(str2);
	free(*args);
	*args = str1;
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
	{
		if (is_parameter(str2))
			parameter_expansion(&str1, &str2, data);
		else
			++str2;
	}
	str2 = ft_strjoin(*args, str1);
	free(str1);
	str1 = ft_strjoin(str2, ++arg_close);
	if (str1 && str2)
		*parg = str1 + ft_strlen(str2);
	free(str2);
	free(*args);
	*args = str1;
}

void	shell_expansion(t_data *data)
{
	char	**args;
	char	*arg;

	args = data->cmds->args;
	if (args == NULL)
		return ;
	while (*args)
	{
		arg = *args;
		while (arg && *arg)
		{
			if (*arg == QUOTE_S || *arg == QUOTE_D)
				quote_removal(args, &arg, *arg, data);
			else if (is_parameter(arg))
				parameter_expansion(args, &arg, data);
			else
				++arg;
		}
		++args;
	}
}
