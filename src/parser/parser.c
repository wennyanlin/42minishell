/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:12:10 by wlin              #+#    #+#             */
/*   Updated: 2024/09/02 03:01:47 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cmd_str(char *str, int i, t_commands *cmd)
{
	cmd->args[i] = ft_strdup(str);
}

void	add_cmd_redirect(t_metachar type, char *filename, t_commands *cmd)
{
	t_redirect	*new_redirect;
	t_redirect	*tmp_redirect;
	t_commands	*tmp;

	new_redirect = malloc(sizeof(t_redirect));
	new_redirect->type = type;
	new_redirect->filename = ft_strdup(filename);
	new_redirect->next = NULL;
	if (!cmd->redirect)
		cmd->redirect = new_redirect;
	else
	{
		tmp = cmd;
		tmp_redirect = tmp->redirect;
		while (tmp_redirect->next)
			tmp_redirect = tmp_redirect->next;
		tmp_redirect->next = new_redirect;
	}
}

void	add_command(t_token **token_lst, t_commands *cmd)
{
	int	i;

	i = -1;
	while (*token_lst && (*token_lst)->metachar != PIPE)
	{
		if ((*token_lst)->metachar > PIPE)
		{
			add_cmd_redirect((*token_lst)->metachar,
				(*token_lst)->next->word, cmd);
			*token_lst = (*token_lst)->next;
		}
		else if ((*token_lst)->word)
		{
			++i;
			add_cmd_str((*token_lst)->word, i, cmd);
		}
		*token_lst = (*token_lst)->next;
	}
}

t_commands	*build_cmd(t_token **token_lst)
{
	int			len;
	t_commands	*cmd;

	cmd = create_cmd_lstnew();
	if (cmd != NULL)
	{
		len = count_cmd_str(*token_lst);
		cmd->args = malloc(sizeof(char *) * (len + 1));
		if (cmd->args != NULL)
		{
			add_command(token_lst, cmd);
			cmd->args[len] = NULL;
		}
	}
	return (cmd);
}

int	parse_tokens(t_data *data)
{
	t_token		*tokens;
	t_commands	*new;

	tokens = data->tokens;
	if (tokens == NULL || validate_cmd_syntax(tokens) == EXIT_FAILURE)
		return (FALSE);
	while (tokens)
	{
		new = build_cmd(&tokens);
		if (new == NULL || new->args == NULL)
			return (FALSE);
		cmd_lst_addback(&data->cmds, new);
		if (tokens && tokens->metachar == PIPE)
			tokens = tokens->next;
	}
	return (TRUE);
}
