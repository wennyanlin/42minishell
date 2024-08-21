/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:35:36 by wlin              #+#    #+#             */
/*   Updated: 2024/08/21 12:11:39 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perror_and_exit(char *file, int code)
{
	int	fd;

	fd = open(file, O_RDWR);
	if (fd == -1 && errno == EISDIR)
		printf("minisell: %s: %s\n", file, strerror(errno));
	else
		perror(file);
	exit(code);
}

void	ft_free_lst(t_token *lst)
{
	t_token	*tmp;

	if (lst == NULL)
		return ;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (tmp->word)
			free(tmp->word);
		tmp->word = NULL;
		free(tmp);
	}
	lst = NULL;
}

void	ft_free_cmds(t_commands *cmds)
{
	t_commands	*tmp;
	t_redirect	*tmp_redirect;

	if (cmds == NULL)
		return ;
	while (cmds)
	{
		free_array(cmds->args);
		while (cmds->redirect)
		{
			free(cmds->redirect->filename);
			cmds->redirect->filename = NULL;
			tmp_redirect = cmds->redirect;
			cmds->redirect = cmds->redirect->next;
			free(tmp_redirect);
		}
		cmds->redirect = NULL;
		tmp = cmds;
		cmds = cmds->next;
		free(tmp);
	}
}

void	start_minishell(void)
{
	t_data		dt;
	char		*line;
	t_commands	*cmds;
	t_token		*token_lst;

	dt.exit_status = 0;
	while (1)
	{
		line = readline(PROMPT);
		token_lst = tokenize(line);
		free(line);
		cmds = parse_tokens(token_lst);
		ft_free_lst(token_lst);
		line = execute_all(cmds, &dt);
		ft_free_cmds(cmds);
		if (line != NULL)
			free(line);
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
