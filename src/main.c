/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:35:36 by wlin              #+#    #+#             */
/*   Updated: 2024/07/14 20:47:16 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "macros.h"
#include "libft.h"
#include "lexer.h"
#include "executor.h"

void	perror_and_exit(char *file, int code)
{
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

char	**convert_lst_to_array(t_token *token_lst)
{
	int		i;
	int		len;
	int		lst_size;
	t_token	*tmp_lst;
	char	**cmd_args;
	
	tmp_lst = token_lst;
	lst_size = 0;
	while (tmp_lst)
	{
		++lst_size;
		tmp_lst = tmp_lst->next;
	}
	cmd_args = malloc(sizeof(char *) * (lst_size + 1));
	if (!cmd_args)
		return (NULL);
	i = 0;
	tmp_lst = token_lst;
	while (tmp_lst)
	{
		len = ft_strlen(tmp_lst->word);
		cmd_args[i] = malloc(sizeof(char) * (len + 1));
		ft_strlcpy(cmd_args[i], tmp_lst->word, (len + 1));
		tmp_lst = tmp_lst->next;
		i++;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}

// t_commands	create_cmd_arr(t_commands *cmd2, t_commands *cmd3, t_redirect *redirect1, t_redirect *redirect3)
// {
// 	char		**arr1;
// 	char		**arr2;
// 	char		**arr3;
// 	t_commands	cmd1;
// 	t_redirect	*redirect1_2 = malloc(sizeof(t_redirect));
	
// 	arr1 = calloc(3, sizeof(char*));
// 	arr1[0] = "ls";
// 	arr1[1] = "-l";
// 	arr1[2] = NULL;
// 	redirect1->filename = "infile1";
// 	redirect1->type = LESS;
// 	redirect1_2->filename = "infile2";
// 	redirect1_2->type = LESS;
// 	redirect1->next = redirect1_2;
// 	redirect1_2->next = NULL;
// 	arr2 = calloc(3, sizeof(char*));
// 	arr2[0] = "grep";
// 	arr2[1] = "src";
// 	arr2[2] = NULL;
// 	arr3 = calloc(3, sizeof(char*));
// 	arr3[0] = "wc";
// 	arr3[1] = "-w";
// 	arr3[2] = NULL;
// 	redirect3->filename = "outfile";
// 	redirect3->type = GREAT;
// 	redirect3->next = NULL;
// 	cmd1.args = arr1;
// 	cmd2->args = arr2;
// 	cmd2->redirect = redirect1;
// 	cmd3->args = arr3;
// 	cmd1.redirect = NULL;
// 	cmd3->redirect = redirect3;
// 	cmd1.next = cmd2;
// 	cmd2->next = cmd3;
// 	cmd3->next = NULL;
// 	return (cmd1);
// }

void	print_parser_cmds(t_commands *cmds)
{
	t_commands	*tmp;
	t_redirect	*tmp_redirect;
	int			i;
	
	tmp = cmds;
	while (tmp != NULL)
	{
		
		i = 0;
		printf("\n============NEW COMMAND============\n\n");
		printf("  WORD:     [");
		while (tmp->args[i])
			printf("[%s], ", tmp->args[i++]);
		printf("\\0]\n");
		tmp_redirect = tmp->redirect;
		printf("  REDIRECT: ");
		while (tmp_redirect)
		{
			printf("%d->", tmp_redirect->type);
			printf("%s->", tmp_redirect->filename);
			tmp_redirect = tmp_redirect->next;
		}
		printf("\n\n===================================\n\n");
		printf("  NEXT->\n");
		tmp = tmp->next;	
	}
	printf("\n");
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_commands	*cmds;
	t_token	*token_lst;

	if (argc == 2 && ft_strncmp(argv[1], "test", 5) == 0)
		test_lexer();
	else if (argc == 2 && ft_strncmp(argv[1], "-v", 3) == 0)
		return (printf("%s, version %s\n", NAME, VERSION), 0);
	else
	{
		while (1)
		{
			line = readline(PROMPT);
			token_lst = tokenize(line);
			free(line);
			cmds = parse_tokens(token_lst);
			// print_parser_cmds(cmds);
			execute_all(cmds, envp);
		}
		// free_array(cmd_arr);
		return (0);
	}
}