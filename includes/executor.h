/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 13:16:12 by wlin              #+#    #+#             */
/*   Updated: 2024/07/27 18:30:11 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
#define EXECUTOR_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include "lexer.h"


typedef struct s_redirect
{
	t_metachar			type;
	char				*filename;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_commands
{
	char				**args;
	struct	s_redirect	*redirect;
	struct	s_commands	*prev;
	struct	s_commands	*next;
}	t_commands;

typedef struct s_process
{
	pid_t				pid;
	int					fd_in;
	int					fd_out;
	int					pipe_fd[2];
	char				*cmd_path;
	char				**command;
	char				**envp;
}	t_process;

typedef struct s_str
{
	char	*value;
	char	**empty;
	int		continue_from_index;
}			t_str;


pid_t	waitpid(pid_t pid, int *status, int options); 

/*======================================LEXER=================================*/

int		str_size(const char *args);
char	*str_cpy(char *src);
int	    char_index(char *args, char ref);
char	*string_concat(char *path, char *cmd);
char    *make_path(char *dir, char *cmd);
char	**split_path(char *string, char separator);
char	*find_cmd_path(char *env, char *cmd);
char	**array_concat(char *shell_path, char **args);
void	free_array(char **array);

/*====================================Parser==================================*/

int 		validate_cmd_syntax(t_token *token_lst);
t_commands  *parse_tokens(t_token *tokens);
void		print_parser_cmds(t_commands *cmds);
int 		is_redirection(t_metachar type);
int			count_cmd_str(t_token *tokens);
t_commands  *create_cmd_lstnew();
void    	cmd_lst_addback(t_commands **cmds, t_commands *new);

/*====================================EXECUTOR================================*/

t_process	init_process(t_commands *cmds, char **envp, int pipe_read_end_prev);
void		child_process(t_process *process);
pid_t 		create_process(t_process *process);
void		fd_dup2(int oldfd, int newfd);
void		execute_command(char *command_path, char **cmd_args, char **envp);
void		perror_and_exit(char *file, int code);
void		execute_all(t_commands *cmds, char **envp);
int 		lst_size(t_commands *cmds);

int 		read_here_doc(char *limiter);

void		ft_free_cmds(t_commands *cmds);
int			is_equal(char *s1, char *s2);

/*==========================BUILTIN==============================*/

void	ft_echo();
void	ft_echo();
void	ft_cd();
void	ft_pwd();
void	ft_export();
void	ft_unset();
void	ft_env();
void	ft_exit();
int		is_builtin(char *cmd);

#endif