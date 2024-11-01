/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:38:36 by rtorrent          #+#    #+#             */
/*   Updated: 2024/11/01 20:09:59 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_lists(t_data *data)
{
	t_token		*next_token;
	t_commands	*next_cmds;
	t_redirect	*next_redirect;

	while (data->tokens)
	{
		next_token = data->tokens->next;
		free(data->tokens->word);
		free(data->tokens);
		data->tokens = next_token;
	}
	while (data->cmds)
	{
		next_cmds = data->cmds->next;
		array_clear(&data->cmds->args);
		while (data->cmds->redirect)
		{
			next_redirect = data->cmds->redirect->next;
			free(data->cmds->redirect->filename);
			free(data->cmds->redirect);
			data->cmds->redirect = next_redirect;
		}
		free(data->cmds);
		data->cmds = next_cmds;
	}
}

void	clear_data(t_data *data)
{
	free(data->line);
	free(data->pid);
	free(data->cmd_path);
	array_clear(&data->env);
	heredoc_iter(data, data->cmds, heredoc_unlink);
	clear_lists(data);
}

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
	array_clear(&data->export_vars);
	exit(code);
}
