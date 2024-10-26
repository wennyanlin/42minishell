/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:52:42 by wlin              #+#    #+#             */
/*   Updated: 2024/10/26 04:44:23 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_newline(int sig)
{
	extern int	g_sigstatus;

	ft_putchar_fd('\n', STDOUT_FILENO);
	g_sigstatus = sig;
}

void	handle_quit(int sig)
{
	ft_putstr_fd("Quit", STDOUT_FILENO);
	handle_newline(sig);
}

void	handle_new_prompt(int sig)
{
	handle_newline(sig);
	rl_replace_line("", TRUE);
	rl_on_new_line();
	rl_redisplay();
}

void	set_signal(enum e_mode mode)
{
	if (mode == DEFAULT)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
	else if (mode == INTERACTIVE)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_new_prompt);
	}
	else if (mode == EXECUTING)
	{
		signal(SIGQUIT, handle_quit);
		signal(SIGINT, handle_newline);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
	else if (mode == HEREDOC_CHILD)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_DFL);
	}
}
