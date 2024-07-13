#include "minishell.h"
#include "executor.h"
#include "macros.h"

//1. Calculate how many pipes
    //1.1. Checks the syntax errors, when after pipe there is no characters???
//2. extract **str and redirs list
    //Loop through the token_lst, find the redirections, else if words

// int count_token_lst_size(t_token *lst)
// {
//     int     len;
//     t_token *tmp_lst;

//     len = 0;
//     tmp_lst = lst;
//     while (tmp_lst)
//     {
//         if (tmp_lst->metachar == PIPE)
//             ++len;
//         tmp_lst = tmp_lst->next;
//     }
//     return (len);
// }

void    add_cmd_str(char *str, int i, t_commands *cmds)
{
    
    cmds->str[i] = ft_strdup(str);
}

void    add_cmd_redirect(t_metachar type, char *filename, t_commands *cmds)
{
   t_redirect   *new_redirect;
   t_commands   *tmp;

   new_redirect = malloc(sizeof(t_redirect));
   new_redirect->type = type;
   new_redirect->filename = ft_strdup(filename);
   new_redirect->next = NULL;
   if (!cmds->redirect)
        cmds->redirect = new_redirect;
    else
    {
        tmp = cmds;
        while (tmp->redirect->next)
            tmp->redirect = tmp->redirect->next;
        tmp->redirect->next = new_redirect;
    }
}

int    count_cmd_str(t_token *tokens)
{
    t_token *tmp;
    int     len;

    tmp = tokens;
    len = 0;
    while (tmp && tmp->metachar >= PIPE)
    {
        if (tmp->metachar > PIPE)
            tmp = tmp->next;
        else
            ++len;
        tmp = tmp->next;
    }
    return (len);
}

t_commands  *create_cmd_lstnew()
{
    t_commands  *new;

    new = malloc(sizeof(t_commands));
    if (!new)
        return (NULL);
    new->str = NULL;
    new->redirect = NULL;
    new->prev = NULL;
    new->next = NULL;
    return (new);
}

void    cmd_lst_addback(t_commands *cmd, t_commands *new)
{
    t_commands  *tmp;

    if (cmd)
    {
        tmp = cmd;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
        new->prev = tmp;
    }
    else
        cmd = new;
}

void build_cmd(t_token *token_lst, t_commands *cmds)
{
    int     i;
    int     len;
    char    **str_arr;

    len = count_cmd_str(token_lst);
    str_arr = malloc(sizeof(char *) * (len + 1));
    if (!cmds->str)
        free_array(cmds->str);
    cmds->str = str_arr;
    i = -1;
    while (token_lst && token_lst->metachar != PIPE)
    {
        if (token_lst && token_lst->metachar > PIPE)
            add_cmd_redirect(token_lst->metachar, token_lst->next->word, cmds);
        else if (token_lst && token_lst->word)
        {
            ++i;
            add_cmd_str(token_lst->word, i, cmds);
        }
        token_lst = token_lst->next;
    }
    cmds->str[len] = NULL;
    
}

t_commands  *parse_tokens(t_token *tokens)
{
    t_commands  *cmds;
    t_commands  *new;

    cmds = NULL;
    while (tokens)
    {
        new = create_cmd_lstnew();
        if (!new)
            return (NULL);
        cmd_lst_addback(cmds, new);
        build_cmd(tokens, cmds);
        tokens = tokens->next;
    }
    return (cmds);
}
