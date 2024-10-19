/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:52:42 by wlin              #+#    #+#             */
/*   Updated: 2024/10/17 14:03:14 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void new_prompt_line(int sig) 
{
    extern int g_sigstatus;
    
	(void)sig;
    ft_putchar_fd('\n', 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
    g_sigstatus = SIGINT_CODE;    
}

void    handle_sigint_child(int sig)
{
    extern int g_sigstatus;
    
    (void)sig;
    ft_putchar_fd('\n', 1);
    if (sig == SIGQUIT)
        g_sigstatus = SIGQUIT_CODE;
    else if (sig == SIGINT)
        g_sigstatus = SIGINT_CODE;
}

void    set_signal(int mode)
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
}