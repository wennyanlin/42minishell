/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:17:03 by wlin              #+#    #+#             */
/*   Updated: 2024/08/13 13:38:25 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prompt_error_message(t_metachar type)
{
	if (type == PIPE)
		printf("minishell: syntax error near unexpected token `%c'\n", C_PIPE);
	else if (type == LESS)
		printf("minishell: syntax error near unexpected token `%c'\n", C_LESS);
	else if (type == LESS_LESS)
		printf("minishell: syntax error near unexpected token `%c%c'\n", C_LESS,
			C_LESS);
	else if (type == GREAT)
		printf("minishell: syntax error near unexpected token `%c'\n", C_GREAT);
	else if (type == GREAT_GREAT)
		printf("minishell: syntax error near unexpected token`%c%c'\n", C_GREAT,
			C_GREAT);
	return (EXIT_FAILURE);
}

int	syntax_error_start_with_pipe(t_token *token_lst)
{
	if (token_lst->prev == NULL || token_lst->next->metachar == PIPE)
		return (prompt_error_message(PIPE));
	else if (is_redirection(token_lst->next->metachar)
		&& token_lst->next->next == NULL)
		return (printf("minishell: syntax error near unexpected "
				"token`newline'\n"), EXIT_FAILURE);
	else if (token_lst->prev == NULL && token_lst->next->word
		&& token_lst->next->next == NULL)
		return (prompt_error_message(PIPE));
	else
		return (EXIT_SUCCESS);
}

int	syntax_error_start_with_redirection(t_token *token_lst)
{
	if (token_lst->next == NULL)
		return (printf("minishell: syntax error near unexpected "
				"token`newline'\n"), EXIT_FAILURE);
	else if (token_lst->next->metachar == PIPE)
		return (prompt_error_message(PIPE));
	else if (is_redirection(token_lst->next->metachar)
		&& token_lst->metachar == token_lst->next->metachar)
		return (prompt_error_message(token_lst->metachar));
	else if (is_redirection(token_lst->next->metachar)
		&& token_lst->metachar != token_lst->next->metachar)
		return (prompt_error_message(token_lst->next->metachar));
	else
		return (EXIT_SUCCESS);
}

int	validate_cmd_syntax(t_token *token_lst)
{
	while (token_lst)
	{
		if (token_lst->metachar == PIPE)
			return (syntax_error_start_with_pipe(token_lst));
		else if (is_redirection(token_lst->metachar))
			return (syntax_error_start_with_redirection(token_lst));
		token_lst = token_lst->next;
	}
	return (EXIT_SUCCESS);
}
