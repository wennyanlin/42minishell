/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:35:36 by wlin              #+#    #+#             */
/*   Updated: 2024/09/04 11:04:14 by rtorrent         ###   ########.fr       */
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
	free(data->pid);
	free(data->cmd_path);
}

void	exit_minishell(t_data *data, char *str, char *error_str, int code)
{
	extern char	**environ;

	if (str)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(error_str, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	clear_data(data);
	array_clear(&environ);
	free(data->exit_status);
	if (str)
		exit(code);
	exit(EXIT_SUCCESS);
}

void	start_minishell(void)
{
	extern char	**environ;
	t_data		dt;

	environ = array_dup(environ);
	dt.exit_status = ft_itoa(0);
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
