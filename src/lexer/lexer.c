/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:07:03 by wlin              #+#    #+#             */
/*   Updated: 2024/06/09 23:45:58 by wlin             ###   ########.fr       */
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



// char *extract_token(int start, int end)
// {
	
// }

void	add_token_lst(t_lst **token_lst, char *new_token)
{
	t_lst	*new_node;

	new_node = create_lst_node();
	lst_add_last(token_lst, new_node);
	init_lst_node();
	
}

int	tokenize_input(t_lst *token_lst, char *input, int start_token)
{
	int		j;
	char	*new_token;
	int		first_quote;
	int		matching_quote;
	int		end_token;
	
	
	j = start_token - 1;
	while (!is_whitespace(input[++j]))
	{
		if (input[j] == QUOTE_S || input[j] == QUOTE_D)
		{
			first_quote = input[j];
			matching_quote = find_matching_quote(input, j, input[j]);
			if (matching_quote != NOT_FOUND)
			{
				end_token = find_end_chars_index(input, j);
				new_token = ft_substr(input, (unsigned int)start_token, end_token - start_token + 1);
				add_token_lst(token_lst, new_token);
				return (end_token);
			}
			//else
				//extract_token();
		}
	}
}

int	handle_input(char *input)
{
	t_lst	*token_lst;
	int		i;

	i = -1;
	while (input[++i])
	{
		if (is_whitespace(input[i]))
			i = skip_spaces(input, i);
		else
            i = tokenize_input(token_lst, input, i);

	}
}
