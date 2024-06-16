/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:07:03 by wlin              #+#    #+#             */
/*   Updated: 2024/06/16 23:29:57 by wlin             ###   ########.fr       */
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



int	add_token(t_lst **token_lst, char *word, t_metachar metachar)
{
	t_lst *new_node;
	t_lst *head;

	head = *token_lst;

	if ((int)head->metachar == UNINITIALIZED)
	{
		head->word = word;
		head->metachar = metachar;	
	} 
	else
	{
		new_node = create_lst_node(word, metachar);
		lst_add_back(token_lst, new_node);
	}
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

int	get_next_token(t_lst **token_lst, char *input, int start)
{
	int	i;
	
	i = start - 1;
	while (input[++i] && !is_whitespace(input[i]))
	{
		if (input[i] == C_PIPE)
			add_token(token_lst, NULL, PIPE);
		else if (input[i] == C_LESS && input[i + 1] != C_LESS)
			add_token(token_lst, NULL, LESS);
		else if (input[i] == C_LESS && input[i + 1] == C_LESS)
			i += add_token(token_lst, NULL, LESS_LESS);
		else if (input[i] == C_GREAT && input[i + 1] != C_GREAT)
			add_token(token_lst, NULL, GREAT);
		else if (input[i] == C_GREAT && input[i + 1] == C_GREAT)
			i += add_token(token_lst, NULL, GREAT_GREAT);
		else
			i = handle_word(token_lst, input, i) - 1;
	}
	return (i);
}

t_lst	*tokenize(char *input)
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
            i = get_next_token(&token_lst, input, i);
		if (!input[i])
			break ;
	}
	printf_list(token_lst);
	return (token_lst);
}


