/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:12:10 by wlin              #+#    #+#             */
/*   Updated: 2024/08/12 16:53:28 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    add_cmd_str(char *str, int i, t_commands *cmd)
{
    cmd->args[i] = ft_strdup(str);
}

void    add_cmd_redirect(t_metachar type, char *filename, t_commands *cmd)
{
   t_redirect   *new_redirect;
   t_redirect   *tmp_redirect;
   t_commands   *tmp;

   new_redirect = malloc(sizeof(t_redirect));
   new_redirect->type = type;
   new_redirect->filename = ft_strdup(filename);
   new_redirect->next = NULL;
   if (!cmd->redirect)
        cmd->redirect = new_redirect;
    else
    {
        tmp = cmd;
        tmp_redirect = tmp->redirect;
        while (tmp_redirect->next)
            tmp_redirect = tmp_redirect->next;
        tmp_redirect->next = new_redirect;
    }
}

void    add_command(t_token **token_lst, t_commands *cmd)
{
    int i;
    
    i = -1;
    while (*token_lst && (*token_lst)->metachar != PIPE)
    {
        if ((*token_lst)->metachar > PIPE)
        {
            add_cmd_redirect((*token_lst)->metachar, (*token_lst)->next->word, cmd);
            *token_lst = (*token_lst)->next;
        }
        else if ((*token_lst)->word)
        {
            ++i;
            add_cmd_str((*token_lst)->word, i, cmd);
        }
        *token_lst = (*token_lst)->next;
    }
}

t_commands *build_cmd(t_token **token_lst)
{
    int     len;
    t_commands  *cmd;

    cmd = create_cmd_lstnew();
    len = count_cmd_str(*token_lst);
    if (len > 0)
    {
        cmd->args = malloc(sizeof(char *) * (len + 1));
        if (!cmd->args)
            free_array(cmd->args);
    }
    add_command(token_lst, cmd);
    if (cmd->args != NULL)
        cmd->args[len] = NULL;
    return (cmd);
}

t_commands  *parse_tokens(t_token *tokens)
{
    t_commands  *cmds;
    t_commands  *new;

    if (validate_cmd_syntax(tokens) == EXIT_FAILURE)
        return (NULL);
    cmds = NULL;
    while (tokens)
    {
        new = build_cmd(&tokens);
        cmd_lst_addback(&cmds, new);
        if (tokens && tokens->metachar == PIPE)
            tokens = tokens->next;
    }
    return (cmds);
}
