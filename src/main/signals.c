/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:52:42 by wlin              #+#    #+#             */
/*   Updated: 2024/10/22 13:40:58 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_prompt_line(int sig)
{
	extern int	g_sigstatus;

	(void)sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
	g_sigstatus = SIGINT;
}

void	handle_sigint_child(int sig)
{
	extern int	g_sigstatus;

	(void)sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	if (sig == SIGQUIT)
		g_sigstatus = SIGQUIT;
	else if (sig == SIGINT)
		g_sigstatus = SIGINT;
}

void	set_signal(int mode)
{
	if (mode == CHILD)
	{
		signal(SIGQUIT, handle_sigint_child);
		signal(SIGINT, handle_sigint_child);
	}
	else if (mode == PARENT)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, new_prompt_line);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_DFL);
	}
}
