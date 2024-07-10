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

// void    add_cmd_redirect(t_metachar metachar, char *filename, t_commands *cmds)
// {
//     cmds->redirect
// }

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
    while (tmp_lst)
    {
        if (tmp_lst->metachar == PIPE)
        {
            while (tokens != tmp_lst)
            {
                i = 0;
                init_cmd_str(tokens, cmds);
                init_cmd_redirect(tokens, cmds);
                if (tokens && tokens->metachar == NONE)
                {
                    add_cmd_str(tokens->word, i, cmds);
                    ++i;
                }
                else if (tokens && tokens->metachar > PIPE && tokens->next->word)
                    add_cmd_redirect(tokens->metachar, tokens->next->word, cmds); //DO I need to init redirect to NULL first?
                tokens = tokens->next;
            }
        }
        tmp_lst = tmp_lst->next;
    }
}