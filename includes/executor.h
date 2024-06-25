/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 13:16:12 by wlin              #+#    #+#             */
/*   Updated: 2024/06/25 15:06:57 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef executor_h
#define executor_h

# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

typedef struct s_commands
{
	char				**str;
	struct	s_commands	*prev;
	struct	s_commands	*next;
}	t_commands;

typedef struct s_exec_state
{
	int		*cmd_idx;
	int		num_cmds;
	char	*cmd_path;
	char	**cmd_args;
	int		fd_in;
	char	**envp;
}	t_exec_state;

typedef struct s_str
{
	char	*value;
	char	**empty;
	int		continue_from_index;
}			t_str;

int		str_size(const char *str);
char	*str_cpy(char *src);
int	    char_index(char *str, char ref);
char	*string_concat(char *path, char *cmd);
char    *make_path(char *dir, char *cmd);
char	**split_path(char *string, char separator);
char	*find_path(char *env, char *cmd);
char	**array_concat(char *shell_path, char **args);
void	free_array(char **array);

void	child_process(int pipe_fd[2], t_exec_state *state);
void 	create_process(t_exec_state *state);
void	fd_dup2(int oldfd, int newfd);
void	execute_command(char *command_path, char **cmd_args, char **envp, int pipe_fd[2]);
void	perror_and_exit(char *file, int code);
void	execute_all(char **cmd_arr, char **envp);

#endif