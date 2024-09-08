/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:35:36 by wlin              #+#    #+#             */
/*   Updated: 2024/09/08 15:27:07 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_data(t_data *data)
{
	t_token		*next_token;
	t_commands	*next_cmds;
	t_redirect	*next_redirect;

	free(data->line);
	while (data->tokens)
	{
		next_token = data->tokens->next;
		free(data->tokens->word);
		free(data->tokens);
		data->tokens = next_token;
	}
	free(data->pid);
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
	free(data->cmd_path);
}

int	error_message(char *source, char *err_str, int code)
{
	ft_putstr_fd(source, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(err_str, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (code);
}

void	exit_minishell(t_data *data, char *source, char *err_str, int code)
{
	clear_data(data);
	array_clear(&data->envp);
	if (source)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		exit(error_message(source, err_str, code));
	}
	exit(EXIT_SUCCESS);
}

void	start_minishell(void)
{
	t_data	dt;

	dt.envp = array_dup(environ);
	environ = dt.envp;
	dt.exit_status = 0;
	dt.tokens = NULL;
	dt.cmds = NULL;
	dt.cmd_path = NULL;
	while (TRUE)
	{
		dt.line = readline(PROMPT);
		if (tokenize(&dt.tokens, dt.line) && parse_tokens(&dt))
			execute_all(&dt, dt.cmds);
		clear_data(&dt);
	}
}

int	main(int argc, char **argv)
{
	if (argc == 2 && ft_strncmp(argv[1], "test", 5) == 0)
		test_lexer();
	else if (argc == 2 && ft_strncmp(argv[1], "-v", 3) == 0)
		return (printf("%s, version %s\n", NAME, VERSION), 0);
	else
		start_minishell();
	return (0);
}
