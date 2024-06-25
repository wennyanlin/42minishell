/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:35:36 by wlin              #+#    #+#             */
/*   Updated: 2024/06/25 22:57:11 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "macros.h"
#include "libft.h"
#include "lexer.h"
#include "executor.h"

int get_wait_status(int status)
{
    int stat_code;

    stat_code = 0;
    if (WIFEXITED(status))
        stat_code = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        stat_code = WTERMSIG(status);
    else if (WIFSTOPPED(status))
        stat_code = WSTOPSIG(status);
    return (stat_code);
}

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

int	main(int argc, char **argv, char **envp)
{
	int		i;
	pid_t	status;
	char	*line;
	char	**cmd_arr;
	t_token	*token_lst;
	t_exec_state	state;

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
			token_lst = tokenize(line);
			free(line);
			cmd_arr = convert_lst_to_array(token_lst);
			ft_free_lst(token_lst);
			state = execute_all(cmd_arr, envp);
			i = -1;
			while (++i < state.num_cmds)
			{
				waitpid(state.pid_arr[i], &status, 0);
				get_wait_status(status);
			}
		}
		free_array(cmd_arr);
		return (0);
	}
}