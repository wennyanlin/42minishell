/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:07:03 by wlin              #+#    #+#             */
/*   Updated: 2024/06/07 01:06:12 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "macros.h"

//1- loop through input, when find spaces, skip it util chars //YES


//2- else if its quotes, find the other one,

	//2.1- if yes, save the characters in between.
	
	//2.2- else, save the one with the rest of chars.


//3- else, either spaces or quotes characters

	//keep tracking if there is quotes until next spaces
	
		//if yes, repeat step 2.1- and result plus the character at the start
			//int	find_matching_quote() -> 
				//if found, output is the matching quote's index; 
				//else, handle_errors(): if not find matching quotes, return error messages
															
		//if not, extract chars til find space

int	find_matching_quote(char *input, int i, char quote);
{
	int	j;

	j = i - 1;
	while (!is_whitespace(input[++j]))
		if (input[j] == quote)
			return (j);
	if (!input[j] || is_whitespace(input[j]))
		return (NOT_FOUND);
}

char *extract_token(int start, int end)
{
	
}


int	get_token(char **token_array, char *input, int i)
{
	int	j;
	int	idx_matching_quote;
	
	j = i + 0;
	// while (!is_whitespace(input[j]) && (input[j] != QUOTE_S || input[j] != QUOTE_D))
	// 	++j;
	if (input[j] == QUOTE_S || input[j] == QUOTE_D)
	{
		idx_matching_quote = find_matching_quote(char *input, int j, char input[j]);
		if (idx_matching_quote != NOT_FOUND)
		{
			extract_token();
			join_token();
		}
		else
			extract_token();
	}
	else
		return (extract_token());
}

int	handle_input(char *input)
{
	char	**token_array;
	int		i;

	i = -1;
	while (input[++i])
	{
		if (is_whitespace(input[i]))
			i = skip_spaces(input, i);
		else if (input[i] == QUOTE_S)
		{}
		else if (input[i] == QUOTE_D)
		{}
		else
            i = get_token(token_array, input, i);

	}
}
