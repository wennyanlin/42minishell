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

// int count_str_size(t_token *tokens)
// {
//     t_token *tmp;
//     int     len;

//     tmp = tokens;
//     len = 0;
//     while (tmp && tmp->metachar != PIPE)
//     {
//         if (tmp->metachar == LESS)
//         {
//             add_cmd_redirect(LESS, tmp->next, tmp);
//             tmp = tmp->next;
//         }
//         else if (tmp->)
//         tmp = tmp->next;
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

void    init_cmd_str(t_token *tokens, t_commands *cmds)
{
    t_token *tmp;
    int     len;

    tmp = tokens;
    len = 0;
    while (tmp && tmp->metachar != PIPE)
    {
        if (tmp->metachar > PIPE)
            tmp = tmp->next;
        else
            ++len;
        tmp = tmp->next;
    }
    cmds->str = malloc(sizeof(char *) * len + 1);
    if (!cmds->str)
        free_array(cmds->str);
}


t_commands  *parse_tokens(t_token *tokens)
{
    t_token     *tmp_lst;
    t_commands  *cmds;
    int         i;

    cmds = malloc(sizeof(t_commands));
    if (!cmds)
        return (NULL);
    cmds->redirect = NULL;
    cmds->prev = NULL;
    cmds->next = NULL;
    tmp_lst = tokens;
    while (tmp_lst)
    {
        // if (tmp_lst->metachar == PIPE)
        // {
        //     i = 0;
        //     while (tokens && tokens != tmp_lst)
        //     {
        //         init_cmd_str(tokens, cmds);
        //         if (tokens && tokens->metachar == NONE)
        //         {
        //             add_cmd_str(tokens->word, i, cmds);
        //             ++i;
        //         }
        //         else if (tokens && tokens->metachar > PIPE && tokens->next->word)
        //             add_cmd_redirect(tokens->metachar, tokens->next->word, cmds); //DO I need to init redirect to NULL first?
        //         tokens = tokens->next;
        //     }
        // }
        tmp_lst = tmp_lst->next;
    }
    return (cmds);
}

//when found redirection, init one redirection property, copy them to it