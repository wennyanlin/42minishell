/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:35:36 by wlin              #+#    #+#             */
/*   Updated: 2024/06/22 13:58:19 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "macros.h"
#include "libft.h"
#include "lexer.h"

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

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*token_lst;
	char	*cmd_args[2] = {"ls", NULL};

	// (void)envp;
	if (argc == 2 && ft_strncmp(argv[1], "test", 5) == 0)
		test_lexer();
	else if (argc == 2 && ft_strncmp(argv[1], "-v", 3) == 0)
		return (printf("%s, version %s\n", NAME, VERSION), 0);
	else
	{
		while (1)
		{
			line = readline(PROMPT);
			printf("'%s'\n", line);
			token_lst = tokenize(line);
			executor(cmd_args, envp);
			free(line);
			ft_free_lst(token_lst);
		}
		return (0);
	}
}