/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:52:42 by wlin              #+#    #+#             */
/*   Updated: 2024/10/17 09:28:22 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void new_prompt_line(int sig) 
{
	(void)sig;
    ft_putchar_fd('\n', 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}


void    handle_sigint_child(int sig)
{
    (void)sig;
    ft_putchar_fd('\n', 1);
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