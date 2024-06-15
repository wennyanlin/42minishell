/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:07:03 by wlin              #+#    #+#             */
/*   Updated: 2024/06/15 23:21:54 by wlin             ###   ########.fr       */
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

	tmp = lst;
	while (tmp)
	{
		printf("value: %s; token: %i\n", tmp->value, tmp->token);
		tmp = tmp->next;
	}
}

void	ft_error(char *input, int start_token)
{
	while (start_token > 0)
	{
		++input;
		--start_token;
	}
	printf("Syntax error at %s\n", input);
	return ;
}

int	add_token(t_lst **token_lst, char *word, int token)
{
	t_lst	*new_node;

	new_node = create_lst_node(word, token);
	lst_add_back(token_lst, new_node);
	return (1);
}

int	handle_quotes(t_lst **token_lst, char *input, int start_token)
{
	int		matching_quote;
	int		end_token;
	char	*word;	
	
	matching_quote = find_matching_quote(input, start_token + 1, input[start_token]);
	if (matching_quote != NOT_FOUND)
	{
		end_token = find_end_chars_index(input, matching_quote);
		word = ft_substr(input, (unsigned int)start_token, end_token - start_token + 1);
		add_token(token_lst, word, NONE);
		return (end_token);
	}
	else
	{
		ft_error(input, start_token);
		exit(EXIT_FAILURE);
	}
	return (1);
}


int	handle_rest(t_lst **token_lst, int i, char *input, int token)
{
	int		j;
	char	*word;

	j = i;
	while (input[j] && !is_delimiter(input[j]))
		j++;
	j -= 1;
	word = ft_substr(input, (unsigned int)i, j - i + 1);
	add_token(token_lst, word, token);
	return (j);
}

int	handle_token(t_lst **token_lst, char *input, int start_token)
{
	int		j;

	j = start_token - 1;
	while (input[++j] && !is_whitespace(input[j]))
	{
		if (input[j] == QUOTE_S || input[j] == QUOTE_D)
			j = handle_quotes(token_lst, input, start_token);
		else if (input[j] == C_PIPE)
			j += add_token(token_lst, NULL, PIPE);
		else if (input[j] == C_LESS && input[j + 1] != C_LESS)
			j += add_token(token_lst, NULL, LESS);
		else if (input[j] == C_LESS && input[j + 1] == C_LESS)
			j += add_token(token_lst, NULL, LESS_LESS) + 1;
		else if (input[j] == C_GREAT && input[j + 1] != C_GREAT)
			j += add_token(token_lst, NULL, GREAT);
		else if (input[j] == C_GREAT && input[j + 1] == C_GREAT)
			j += add_token(token_lst, NULL, GREAT_GREAT) + 1;
		else
			j = handle_rest(token_lst, j, input, 0);
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
		printf_list(token_lst);
		if (!input[i])
			break ;
	}
}
