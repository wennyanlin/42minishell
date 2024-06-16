/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:07:03 by wlin              #+#    #+#             */
/*   Updated: 2024/06/16 13:12:36 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "macros.h"

//if we found matching quote, keep checking chars after matching quote until spaces
	//if found more chars, 
		//tokenize the whole string skipping the quotes
	//else is an error case
	//keep tracking if there is quotes until next spaces

void	printf_list(t_lst *lst)
{
	t_lst	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		if (tmp->value && tmp->token == 0)
			printf("`%s`  =>  ", tmp->value);	
		else if (!tmp->value && tmp->token != 0)
			printf("%i  =>  ", tmp->token);
		else 
			printf("ERROR! `%s` %i, ",  tmp->value, tmp->token);
		tmp = tmp->next;
		++i;
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

int	add_token(t_lst **token_lst, char *word, int token)
{
	t_lst	*new_node;

	new_node = create_lst_node(word, token);
	lst_add_back(token_lst, new_node);
	return (1);
}

int	handle_quotes(char *input, int start)
{
	int		matching_quote;
	
	matching_quote = find_matching_quote(input, start + 1, input[start]);
	if (matching_quote == NOT_FOUND)
	{
		ft_error(input, start);
		exit(EXIT_FAILURE);
	}
	return (matching_quote);
}

int	handle_word(t_lst **token_lst, char *input, int start)
{
	int		i;
	char	*word;

	i = start - 1;
	while (input[++i])
	{
		if (input[i] == QUOTE_D || input[i] == QUOTE_S)
			i = handle_quotes(input, i);
		else if (is_delimiter(input[i]) == TRUE)
			break ;
	}
	word = ft_substr(input, (unsigned int)start, i - start);
	add_token(token_lst, word, NONE);
	return (i);
}

int	handle_token(t_lst **token_lst, char *input, int start)
{
	int		j;

	j = start - 1;
	while (input[++j] && !is_whitespace(input[j]))
	{
		if (input[j] == C_PIPE)
			add_token(token_lst, NULL, PIPE);
		else if (input[j] == C_LESS && input[j + 1] != C_LESS)
			add_token(token_lst, NULL, LESS);
		else if (input[j] == C_LESS && input[j + 1] == C_LESS)
			j += add_token(token_lst, NULL, LESS_LESS);
		else if (input[j] == C_GREAT && input[j + 1] != C_GREAT)
			add_token(token_lst, NULL, GREAT);
		else if (input[j] == C_GREAT && input[j + 1] == C_GREAT)
			j += add_token(token_lst, NULL, GREAT_GREAT);
		else
			j = handle_word(token_lst, input, j);
	}
	return (j);
}

void	handle_input(char *input)
{
	t_lst	*token_lst;
	int		i;

	i = -1;
	token_lst = create_lst_node(NULL, -1);
	while (input[++i])
	{
		if (is_whitespace(input[i]))
			i = skip_spaces(input, i);
		else
            i = handle_token(&token_lst, input, i);
		if (!input[i])
			break ;
	}
	printf_list(token_lst);
}
