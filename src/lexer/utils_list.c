/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:59:45 by wlin              #+#    #+#             */
/*   Updated: 2024/07/13 19:12:30 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "macros.h"

t_token	*create_lst_node(char *word, int metachar)
{
	t_token   *node;
    
    node = malloc(sizeof(t_token));
    if (!node)
        exit(EXIT_FAILURE);
    node->word = word;
    node->metachar = metachar;
    node->next = NULL;
    node->prev = NULL;
    return (node);
}

void    lst_add_back(t_token **token_lst, t_token *new_node)
{
    t_token   *tmp;

    if (*token_lst)
    {
        tmp = *token_lst;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_node;
        new_node->prev = tmp;
    }
    else
        *token_lst = new_node;
}

void	printf_list(t_token *lst)
{
	t_token	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->word && tmp->metachar == 0)
			printf("`%s`  =>  ", tmp->word);	
		else if (!tmp->word && tmp->metachar != 0)
			printf("%i  =>  ", tmp->metachar);
		else 
			printf("%sERROR!%s `%s` %i, ", RED, tmp->word, RESET, tmp->metachar);
		tmp = tmp->next;
	}
	printf("null\n");
}

void	ft_error(char *input, int start)
{
	while (start > 0)
	{
		++input;
		--start;
	}
	printf("Syntax error at `%s`\n", input);
	return ;
}