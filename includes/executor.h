/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 13:16:12 by wlin              #+#    #+#             */
/*   Updated: 2024/06/22 13:53:31 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef executor_h
#define executor_h

# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

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

#endif