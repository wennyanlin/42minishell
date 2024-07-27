/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:17:03 by wlin              #+#    #+#             */
/*   Updated: 2024/07/27 18:17:56 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "macros.h"

int    prompt_error_message(t_metachar type)
{
    if (type == PIPE)
        printf("minishell: syntax error near unexpected token `%c'\n", C_PIPE);
    else if (type == LESS)
        printf("minishell: syntax error near unexpected token `%c'\n", C_LESS);
    else if (type == LESS_LESS)
        printf("minishell: syntax error near unexpected token `%c%c'\n", C_LESS
            , C_LESS);
    else if (type == GREAT)
        printf("minishell: syntax error near unexpected token `%c'\n", C_GREAT);
    else if (type == GREAT_GREAT)
        printf("minishell: syntax error near unexpected token`%c%c'\n", C_GREAT
            , C_GREAT);
    return (EXIT_FAILURE);
}

int validate_cmd_syntax(t_token *token_lst)
{
    t_token *tmp;

    tmp = token_lst;
    while (tmp)
    {
        if (tmp->metachar == PIPE)
        {
            if (tmp->prev == NULL || tmp->next->metachar == PIPE)
                return (prompt_error_message(PIPE));
            else if (is_redirection(tmp->next->metachar) && tmp->next->next == NULL)
                return (printf("minishell: syntax error near unexpected token`newline'\n"), EXIT_FAILURE);
            else if (tmp->next->word && tmp->next->next == NULL)
                return (prompt_error_message(PIPE));
        }
        else if (is_redirection(tmp->metachar))
        {
            if (tmp->next == NULL)
                return (printf("minishell: syntax error near unexpected token`newline'\n"), EXIT_FAILURE);
            else if (tmp->next->metachar == PIPE)
                return (prompt_error_message(PIPE));
            else if (is_redirection(tmp->next->metachar) && tmp->metachar == tmp->next->metachar)
                return (prompt_error_message(tmp->metachar));
            else if (is_redirection(tmp->next->metachar) && tmp->metachar != tmp->next->metachar)
                return (prompt_error_message(tmp->next->metachar));
        }
        tmp = tmp->next;
    }
    return (EXIT_SUCCESS);
}