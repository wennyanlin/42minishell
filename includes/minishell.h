/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:32:39 by wlin              #+#    #+#             */
/*   Updated: 2024/06/01 17:22:00 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "../src/readline/readline.h"
# include "../src/readline/history.h"
# include "../src/libft/libft.h"

typedef struct s_toke
{
	char	*value;
	char	*type;
}	t_toke;

# endif
