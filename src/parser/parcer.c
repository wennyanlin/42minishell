#include "minishell.h"
#include "executor.h"
#include "macros.h"

//1. Calculate how many pipes
    //1.1. Checks the syntax errors, when after pipe there is no characters???
//2. extract **str and redirs list
    //Loop through the token_lst, find the redirections, else if words

int count_token_lst_size(t_token *lst)
{
    int     len;
    t_token *tmp_lst;

    len = 0;
    tmp_lst = lst;
    while (tmp_lst)
    {
        if (tmp_lst->metachar == PIPE)
            ++len;
        tmp_lst = tmp_lst->next;
    }
    return (len);
}

t_commands  *parse_token_lst(t_token *token_lst)
{
    t_token     *tmp_lst;
    t_commands  *cmds;
    int         len;

    len = 0;
    // cmds = malloc(sizeof(t_commands))
    while (tmp_lst)
    {
        if (tmp_lst->metachar == PIPE)
        {
            while (token_lst != tmp_lst)
            {
                if (token_lst->word)
                {
                    //count the list_size, do malloc of the t_command->str size

                    //copy the str into str_array propoty
                }
            }
            len = 0;
        }
        else
            ++len;
        tmp_lst = tmp_lst->next;
    }
}