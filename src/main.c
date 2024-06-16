/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:35:36 by wlin              #+#    #+#             */
/*   Updated: 2024/06/16 23:10:00 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "macros.h"
#include "libft.h"
#include "lexer.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;

	(void)env;
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
			tokenize(line);
			free(line);
		}
		return (0);
	}
}