/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:35:36 by wlin              #+#    #+#             */
/*   Updated: 2024/10/24 12:50:41 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_lists(t_data *data)
{
	t_token		*next_token;
	t_commands	*next_cmds;
	t_redirect	*next_redirect;

	while (data->tokens)
	{
		next_token = data->tokens->next;
		free(data->tokens->word);
		free(data->tokens);
		data->tokens = next_token;
	}
	while (data->cmds)
	{
		next_cmds = data->cmds->next;
		array_clear(&data->cmds->args);
		while (data->cmds->redirect)
		{
			next_redirect = data->cmds->redirect->next;
			free(data->cmds->redirect->filename);
			free(data->cmds->redirect);
			data->cmds->redirect = next_redirect;
		}
		free(data->cmds);
		data->cmds = next_cmds;
	}
}

void	clear_data(t_data *data)
{
	free(data->line);
	free(data->pid);
	free(data->cmd_path);
	heredoc_iter(data, data->cmds, heredoc_unlink);
	clear_lists(data);
}

static void	reset_data(t_data *data)
{
	data->tokens = NULL;
	data->cmds = NULL;
	data->pid = NULL;
	data->cmd_path = NULL;
}

int	g_sigstatus;

static void	start_minishell(void)
{
	t_data	dt;

	dt.export_vars = array_dup(environ);
// TODO **** Increse SHLVL variable by one + export PWD
	dt.exit_status = 0;
	while (TRUE)
	{
		reset_data(&dt);
		set_signal(PARENT);
		g_sigstatus = 0;
		dt.line = readline(PROMPT);
		if (g_sigstatus != 0)
			dt.exit_status = FATALSIGNAL + g_sigstatus;
		if (dt.line && dt.line[0])
			add_history(dt.line);
		if (tokenize(&dt.tokens, dt.line) && parse_tokens(&dt))
			if (heredoc_iter(&dt, dt.cmds, heredoc_fork) == 0)
				execute_all(&dt, dt.cmds);
		if (dt.line == NULL)
			bt_exit(1, NULL, &dt);
		clear_data(&dt);
	}
}

int	main(int argc, char **argv)
{
	if (argc == 2 && ft_strncmp(argv[1], "test", 5) == 0)
		test_lexer();
	else if (argc == 2 && ft_strncmp(argv[1], "-v", 3) == 0)
		return (printf("%s, version %s\n", SHNAME, VERSION), 0);
	else
		start_minishell();
	return (0);
}
