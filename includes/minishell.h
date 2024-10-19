/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 13:16:12 by wlin              #+#    #+#             */
/*   Updated: 2024/10/19 13:44:15 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

# define VERSION "0.1"
# define SHNAME "minishell"
# define HEREDOC_PREFIX "/tmp/tmp_heredoc"

# define BLUE "\033[1;34m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"

# define PROMPT "\033[1;34mminishell%\033[0m "
# define HEREDOC_PROMPT "> "

# define TRUE 1
# define FALSE 0
# define UNINITIALIZED -1
# define NOT_FOUND -1
# define INVALID -1
# define NONE 0

# define UNIT_SEPARATOR 31
# define QUOTE_D 34
# define DOLLAR 36
# define QUOTE_S 39
# define MINUS 45
# define C_LESS 60
# define EQUALS 61
# define C_GREAT 62
# define QUESTION 63
# define UNDERSCORE 95
# define C_PIPE 124

/*
  expansor flags:
    QRM: quote removal
    INQ: inside quotes
    EXP: expand parameters
    IQU: is question
    WSP: word split
*/

# define QRM 001
# define INQ 002
# define EXP 004
# define IQU 010
# define WSP 020

# define NEGATIVE 0
# define CHILD 0
# define PARENT 1
# define WR 1
# define RD 0

# define NOTEXECUTABLE 126
# define NOTFOUND 127
# define FATALSIGNAL 128

# define SIGINT_CODE 130
# define SIGQUIT_CODE 131

typedef enum e_metachar
{
	UNSET = -1,
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS
}	t_metachar;

typedef struct s_str
{
	char	*value;
	char	**empty;
	int		continue_from_index;
}	t_str;

typedef struct s_token
{
	char			*word;
	t_metachar		metachar;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

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

typedef struct s_data
{
	int			exit_status;
	char		**envp;
	char		*line;
	t_token		*tokens;
	t_commands	*cmds;
	pid_t		*pid;
	char		*cmd_path;
}	t_data;

typedef int	(*t_bfunc)(int argc, char *argv[], t_data *data);

typedef struct s_process
{
	pid_t		pid;
	int			fd_in;
	int			fd_out;
	int			pipe_fd[2];
	char		*cmd_path;
	t_bfunc		builtin;
	t_commands	*command;
}	t_process;

/*===================================MINISHELL================================*/

void		clear_data(t_data *data);
int			error_message(int code, int n, ...);
void		exit_minishell(t_data *data, int code, int n, ...);
void		set_signal(int mode);

/*======================================LEXER=================================*/

void		ft_error(char *input, int start);
// void		printf_list(t_token *lst);
int			is_delimiter(char c);
t_token		*create_lst_node(char *word, int metachar);
void		lst_add_back(t_token **token_lst, t_token *new_node);
int			find_matching_quote(char *input, int i, char quote);
int			tokenize(t_token **token_lst, char *input);

void		test_lexer(void);
void		free_token_lst(t_token **token_lst);

/*====================================PARSER==================================*/

int			validate_cmd_syntax(t_token *token_lst);
int			parse_tokens(t_data *data);
void		print_parser_cmds(t_commands *cmds);
int			is_redirection(t_metachar type);
int			count_cmd_str(t_token *tokens);
t_commands	*create_cmd_lstnew(void);
void		cmd_lst_addback(t_commands **cmds, t_commands *new);

/*====================================EXECUTOR================================*/

pid_t		create_process(t_data *data, t_process *process);
void		execute_all(t_data *data, t_commands *cmds);
void		fd_dup2(t_data *data, int oldfd, int newfd);
char		*find_cmd_path(t_data *data, char *cmd);
void		get_value(char **pstr, unsigned int flags);
void		heredoc_iter(t_data *data, t_commands *cmd,
				void (*f)(t_data *, char **));
void		heredoc_read(t_data *data, char **pword);
void		heredoc_unlink(t_data *data, char **pfilename);
void		init_process(t_data *data, t_process *process);
int			lst_size(t_commands *cmds);
void		shell_expansion(t_data *data, char ***pargs, unsigned int flags);
char		**split_path(char *string, char separator);

/*==================================BUILTINS==================================*/

int			bt_cd(int argc, char *argv[], t_data *data);
int			bt_echo(int argc, char *argv[], t_data *data);
int			bt_env(int argc, char *argv[], t_data *data);
int			bt_exit(int argc, char *argv[], t_data *data);
int			bt_export(int argc, char *argv[], t_data *data);
int			bt_pwd(int argc, char *argv[], t_data *data);
int			bt_unset(int argc, char *argv[], t_data *data);
int			is_builtin(t_bfunc *dst, char *cmd);

/*===============================AUXILIARY FUNCTIONS==========================*/

char		**array_add_front(char ***parray, char *str);
void		array_clear(char ***parray);
char		**array_dup(char **array);
char		**array_join(char **array1, char **array2);
size_t		array_len(char **array);
char		**array_merge_back(char ***parray1, char **array2);
int			char_index(char *args, char ref);
int			find_end_chars_index(char *input, int i);
int			is_equal(char *s1, char *s2);
int			is_whitespace(char c);
int			skip_spaces(char *str, int i);

#endif
