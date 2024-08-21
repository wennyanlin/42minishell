/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:17:03 by wlin              #+#    #+#             */
/*   Updated: 2024/08/21 16:33:25 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prompt_error_message(t_metachar type)
{
	if (type == PIPE)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (type == LESS)
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
	else if (type == LESS_LESS)
		ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
	else if (type == GREAT)
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
	else if (type == GREAT_GREAT)
		ft_putstr_fd("minishell: syntax error near unexpected token`>>'\n", 2);
	return (EXIT_FAILURE);
}

int	check_pipe_error(t_token *token_lst)
{
	if (token_lst->prev == NULL || token_lst->next == NULL
		|| token_lst->next->metachar == PIPE)
		return (prompt_error_message(PIPE));
	else if (is_redirection(token_lst->next->metachar)
		&& token_lst->next->next == NULL)
		return (ft_putstr_fd("minishell: syntax error near unexpected "
				"token`newline'\n", STDERR_FILENO), EXIT_FAILURE);
	else if (token_lst->prev == NULL && token_lst->next->word
		&& token_lst->next->next == NULL)
		return (prompt_error_message(PIPE));
	else
		return (EXIT_SUCCESS);
}

int	check_redirection_error(t_token *token_lst)
{
	if (token_lst->next == NULL)
		return (ft_putstr_fd("minishell: syntax error near unexpected "
				"token`newline'\n", STDERR_FILENO), EXIT_FAILURE);
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
		if (token_lst->metachar == PIPE
			&& check_pipe_error(token_lst) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		else if (is_redirection(token_lst->metachar)
			&& check_redirection_error(token_lst) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		token_lst = token_lst->next;
	}
	return (EXIT_SUCCESS);
}
