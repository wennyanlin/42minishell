/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglanuss <aglanuss@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:44:59 by aglanuss          #+#    #+#             */
/*   Updated: 2024/06/11 12:54:02 by aglanuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

typedef struct	s_command
{
	char	**str;
	struct s_command	*prev;
	struct s_command	*next;
}								t_command;

t_command	*new_command_node(char **str);
void			add_command_node(t_command **commands_lst, t_command *new_command);

#endif