/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:35:36 by wlin              #+#    #+#             */
/*   Updated: 2024/06/23 19:22:28 by wlin             ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*token_lst;

	// (void)envp;
	if (argc == 2 && ft_strncmp(argv[1], "test", 5) == 0)
		test_lexer();
	else if (argc == 2 && ft_strncmp(argv[1], "-v", 3) == 0)
		return (printf("%s, version %s\n", NAME, VERSION), 0);
	else
	{
		while (1)
		{
			printf("READING\n");
			line = readline(PROMPT);
			printf("READ\n");
			printf("'%s'\n", line);
			token_lst = tokenize(line);
			// executor(convert_lst_to_array(token_lst), envp);
			execute_all(convert_lst_to_array(token_lst), envp);
			free(line);
			ft_free_lst(token_lst);
		}
		return (0);
	}
}