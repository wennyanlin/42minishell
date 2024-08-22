/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:35:36 by wlin              #+#    #+#             */
/*   Updated: 2024/08/21 16:25:48 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perror_and_exit(char *file, int code)
{
	int	fd;

	fd = open(file, O_RDWR);
	if (fd == -1 && errno == EISDIR)
	{
		ft_putstr_fd("minisell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	else
		perror(file);
	exit(code);
}

void	free_token_lst(t_token **plst)
{
	t_token	*next;

	while (*plst)
	{
		next = (*plst)->next;
		free((*plst)->word);
		free(*plst);
		*plst = next;
	}
}

void	free_cmds_lst(t_commands **pcmds)
{
	t_commands	*next_cmds;
	t_redirect	*redirect;
	t_redirect	*next_redirect;

	while (*pcmds)
	{
		next_cmds = (*pcmds)->next;
		free_array((*pcmds)->args);
		redirect = (*pcmds)->redirect;
		while (redirect)
		{
			next_redirect = redirect->next;
			free(redirect->filename);
			free(redirect);
			redirect = next_redirect;
		}
		free(*pcmds);
		*pcmds = next_cmds;
	}
}

void	start_minishell(void)
{
	t_data		dt;
	char		*line;
	t_commands	*cmds;
	t_token		*token_lst;

	dt.exit_status = ft_itoa(0);
	while (1)
	{
		line = readline(PROMPT);
		token_lst = tokenize(line);
		free(line);
		cmds = parse_tokens(token_lst);
		free_token_lst(&token_lst);
		execute_all(cmds, &dt);
		free_cmds_lst(&cmds);
	}
	free(dt.exit_status);
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
