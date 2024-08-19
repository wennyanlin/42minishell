/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 13:16:12 by wlin              #+#    #+#             */
/*   Updated: 2024/08/19 16:37:23 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

# define SP 40

# define VERSION "0.1"
# define BLUE "\033[1;34m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"
# define NAME "minishell"
# define PROMPT "\033[1;34mminishell% \033[0m"
# define HEREDOC_PROMPT "> "

# define TRUE 1
# define FALSE 0
# define UNINITIALIZED -1
# define NOT_FOUND -1
# define INVALID -1
# define NONE 0

# define QUOTE_S 39
# define QUOTE_D 34
# define DOLLAR 36
# define C_LESS 60
# define C_GREAT 62
# define QUESTION 63
# define UNDERSCORE 95
# define C_PIPE 124

# define EXIT_FAILURE 1

# define NEGATIVE 0
# define CHILD 0
# define WR 1
# define RD 0

typedef enum e_metachar
{
	UNSET = -1,
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS
}	t_metachar;

typedef struct s_data
{
	t_list	*env;
	char	*exit_status;
}	t_data;

typedef struct s_var
{
	char	*name;
	char	*value;
}	t_var;

typedef struct s_redirect
{
	t_metachar			type;
	char				*filename;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_commands
{
	char				**args;
	struct s_redirect	*redirect;
	struct s_commands	*prev;
	struct s_commands	*next;
}	t_commands;

typedef struct s_token
{
	char			*word;
	t_metachar		metachar;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_process
{
	pid_t	pid;
	int		fd_in;
	int		fd_out;
	int		pipe_fd[2];
	char	*cmd_path;
	char	**command;
	char	**envp;
}	t_process;

typedef struct s_str
{
	char	*value;
	char	**empty;
	int		continue_from_index;
}	t_str;

pid_t		waitpid(pid_t pid, int *status, int options);

/*=================================ENVIRONMENT================================*/

void		del_data(t_data *data);
char		*get_lst_env(t_list *lst, const char *identifier);
char		**lst_to_array(t_list *lst);
void		new_lst_env(t_list **plst, char **envp);

/*======================================LEXER=================================*/

int			str_size(const char *args);
char		*str_cpy(char *src);
int			char_index(char *args, char ref);
char		*string_concat(char *path, char *cmd);
char		*make_path(char *dir, char *cmd);
char		**split_path(char *string, char separator);
char		*find_cmd_path(char *env, char *cmd);
char		**array_concat(char *shell_path, char **args);
void		free_array(char **array);
void		ft_error(char *input, int start);
void		printf_list(t_token *lst);
int			is_whitespace(char c);
int			skip_spaces(char *str, int i);
int			is_delimiter(char c);
t_token		*create_lst_node(char *word, int metachar);
void		lst_add_back(t_token **token_lst, t_token *new_node);
int			find_matching_quote(char *input, int i, char quote);
int			find_end_chars_index(char *input, int i);
t_token		*tokenize(char *input);
void		test_lexer(void);
void		ft_free_lst(t_token *lst);

/*====================================PARSER==================================*/

int			validate_cmd_syntax(t_token *token_lst);
t_commands	*parse_tokens(t_token *tokens);
void		print_parser_cmds(t_commands *cmds);
int			is_redirection(t_metachar type);
int			count_cmd_str(t_token *tokens);
t_commands	*create_cmd_lstnew(void);
void		cmd_lst_addback(t_commands **cmds, t_commands *new);

/*====================================EXECUTOR================================*/

void		shell_expansion(char **args, t_data *data);
t_process	init_process(t_commands *cmds, char **envp, char *path,
				int pipe_read_end_prev);
void		child_process(t_process *process);
pid_t		create_process(t_process *process);
void		fd_dup2(int oldfd, int newfd);
void		execute_command(char *command_path, char **cmd_args, char **envp);
void		perror_and_exit(char *file, int code);
char		*execute_all(t_commands *cmds, t_data *data);
int			lst_size(t_commands *cmds);

int			read_here_doc(char *limiter);
int			directory_error(char *cmd);

void		ft_free_cmds(t_commands *cmds);
int			is_equal(char *s1, char *s2);

/*==========================BUILTIN==============================*/

void		ft_echo(void);
void		ft_echo(void);
void		ft_cd(void);
void		ft_pwd(void);
void		ft_export(void);
void		ft_unset(void);
void		ft_env(void);
void		ft_exit(void);
int			is_builtin(char *cmd);

#endif
