/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:52:42 by wlin              #+#    #+#             */
/*   Updated: 2024/10/26 16:35:41 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_new_prompt(int sig)
{
	extern int	g_sigstatus;

	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", TRUE);
	rl_on_new_line();
	rl_redisplay();
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
		signal(SIGINT, handle_new_prompt);
	}
	else if (mode == EXECUTING)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_DFL);
	}
}
