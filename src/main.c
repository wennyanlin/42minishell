/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:35:36 by wlin              #+#    #+#             */
/*   Updated: 2024/08/14 06:12:58 by rtorrent         ###   ########.fr       */
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

// void	print_parser_cmds(t_commands *cmds)
// {
// 	t_commands	*tmp;
// 	t_redirect	*tmp_redirect;
// 	int			i;

// 	tmp = cmds;
// 	while (tmp != NULL)
// 	{

// 		i = 0;
// 		printf("\n============NEW COMMAND============\n\n");
// 		printf("  WORD:     [");
// 		while (tmp->args[i])
// 			printf("[%s], ", tmp->args[i++]);
// 		printf("\\0]\n");
// 		tmp_redirect = tmp->redirect;
// 		printf("  REDIRECT: ");
// 		while (tmp_redirect)
// 		{
// 			printf("%d->", tmp_redirect->type);
// 			printf("%s->", tmp_redirect->filename);
// 			tmp_redirect = tmp_redirect->next;
// 		}
// 		printf("\n\n===================================\n\n");
// 		printf("  NEXT->\n");
// 		tmp = tmp->next;	
// 	}
// 	printf("\n");
// }

// void	trim_whitespaces(char *line)
// {
// 	int	start_back;
// 	int	front;

// 	if (!line)
// 		return ;
// 	start_back = ft_strlen(line) - 1;
// 	while (start_back >= 0 && is_whitespace(line[start_back]))
// 	{
// 		line[start_back] = '\0';
// 		start_back--;
// 	}
// 	start_back++;
// 	front = 0;
// 	while (line[front] && is_whitespace(line[front]))
// 		front++;
// 	if (front > 0)
// 		ft_memmove(line, line + front, start_back - front + 1);
// }

void	start_minishell(char **envp)
{
	t_data		dt;
	char		*line;
	t_commands	*cmds;
	t_token		*token_lst;

	dt = (t_data){NULL, 0, ft_itoa(0)};
	new_lst_env(&dt.env, envp);
	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL || *line == '\0')
			continue ;
		token_lst = tokenize(line);
		free(line);
		if (token_lst == NULL)
			continue ;
		cmds = parse_tokens(token_lst);
		if (cmds == NULL)
			continue ;
		ft_free_lst(token_lst);
		execute_all(cmds, &dt);
		ft_free_cmds(cmds);
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 2 && ft_strncmp(argv[1], "test", 5) == 0)
		test_lexer();
	else if (argc == 2 && ft_strncmp(argv[1], "-v", 3) == 0)
		return (printf("%s, version %s\n", NAME, VERSION), 0);
	else
		start_minishell(envp);
	return (0);
}
