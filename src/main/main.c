/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:35:36 by wlin              #+#    #+#             */
/*   Updated: 2024/11/02 16:02:58 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigstatus;

static void	reset_data(t_data *data)
{
	data->tokens = NULL;
	data->cmds = NULL;
	data->pid = NULL;
	data->cmd_path = NULL;
	g_sigstatus = 0;
	set_signal(INTERACTIVE);
}

static int	smooth_operator(t_data *data)
{
	int		exit_code;

	if (tokenize(&data->tokens, data->line) && parse_tokens(data))
	{
		set_signal(EXECUTING);
		exit_code = heredoc_iter(data, data->cmds, heredoc_fork);
		if (exit_code == EXIT_SUCCESS)
			exit_code = execute_all(data, data->cmds);
		return (exit_code);
	}
	return (EXIT_FAILURE);
}

static void	minishell_loop(t_data *data)
{
	while (TRUE)
	{
		reset_data(data);
		data->line = readline(PROMPT);
		if (g_sigstatus != 0)
			data->exit_status = FATALSIGNAL + g_sigstatus;
		if (data->line == NULL)
			bt_exit(1, (char *[2]){"exit", NULL}, data);
		if (data->line[0])
		{
			add_history(data->line);
			data->exit_status = smooth_operator(data);
			if (data->exit_status > FATALSIGNAL)
				ft_putchar_fd('\n', STDOUT_FILENO);
		}
		clear_data(data);
	}
}

static void	init_minishell(void)
{
	t_data	dt;
	char	pwd[PATH_MAX];
	char	*shlvl;
	int		shlvl_value;

	dt.export_vars = array_dup(environ);
	dt.env = NULL;
	dt.exit_status = 0;
	set_in_env(&dt.export_vars, "PWD", getcwd(pwd, PATH_MAX));
	shlvl = getenv("SHLVL");
	shlvl_value = 0;
	if (shlvl)
		shlvl_value = ft_atoi(shlvl);
	if (shlvl_value < 0)
		shlvl_value = -1;
	shlvl = ft_itoa(++shlvl_value);
	set_in_env(&dt.export_vars, "SHLVL", shlvl);
	free(shlvl);
	minishell_loop(&dt);
}

int	main(int argc, char **argv)
{
	if (argc == 2 && ft_strncmp(argv[1], "test", 5) == 0)
		test_lexer();
	else if (argc == 2 && ft_strncmp(argv[1], "-v", 3) == 0)
		printf("%s, version %s\n", SHNAME, VERSION);
	else
		init_minishell();
}
