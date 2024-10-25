/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:52:42 by wlin              #+#    #+#             */
/*   Updated: 2024/10/25 14:19:05 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_prompt_line(int sig)
{
	extern int	g_sigstatus;

	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", TRUE);
	rl_on_new_line();
	rl_redisplay();
	g_sigstatus = sig;
}

void	handle_sigint_child(int sig)
{
	extern int	g_sigstatus;

	ft_putchar_fd('\n', STDOUT_FILENO);
	g_sigstatus = sig;
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
		signal(SIGINT, new_prompt_line);
	}
	else if (mode == EXECUTING)
	{
		signal(SIGQUIT, handle_sigint_child);
		signal(SIGINT, handle_sigint_child);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_DFL);
	}
}
