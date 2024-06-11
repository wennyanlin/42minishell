/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglanuss <aglanuss@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:35:36 by wlin              #+#    #+#             */
/*   Updated: 2024/06/21 13:12:34 by aglanuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "macros.h"
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

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_token	*token_lst;

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
			token_lst = tokenize(line);
			free(line);
			ft_free_lst(token_lst);
		}
		return (0);
	}

// int	main(/*int argc, char **argv, char **env*/)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = readline("\e[1;34mminishell$\e[0m ");
// 		printf("%s\n", line);
// 	}
// 	return (0);
// }


int main()
{
  // Crear y asignar memoria para los nodos
    t_lexer *node1 = (t_lexer*)malloc(sizeof(t_lexer));
    t_lexer *node2 = (t_lexer*)malloc(sizeof(t_lexer));
    t_lexer *node3 = (t_lexer*)malloc(sizeof(t_lexer));
    t_lexer *node4 = (t_lexer*)malloc(sizeof(t_lexer));
    t_lexer *node5 = (t_lexer*)malloc(sizeof(t_lexer));
    t_lexer *node6 = (t_lexer*)malloc(sizeof(t_lexer));
    t_lexer *node7 = (t_lexer*)malloc(sizeof(t_lexer));

    // Inicializar los valores de los nodos
    node1->value = "ls";
    node1->type = 0;
    node1->prev = NULL;
    node1->next = node2;

    node2->value = "-l";
    node2->type = 0;
    node2->prev = node1;
    node2->next = node3;

    node3->value = "|";
    node3->type = PIPE;
    node3->prev = node2;
    node3->next = node4;

    node4->value = "echo";
    node4->type = 0;
    node4->prev = node3;
    node4->next = node5;

    node5->value = "hola";
    node5->type = 0;
    node5->prev = node4;
    node5->next = node6;

    node6->value = ">";
    node6->type = GREAT;
    node6->prev = node5;
    node6->next = node7;

    node7->value = "file1";
    node7->type = 0;
    node7->prev = node6;
    node7->next = NULL;

	// Imprimir la lista para verificar
	t_lexer **head = &node1;
	t_lexer *current = *head;

	printf("First print:\n");
	while (current)
	{
		printf("%s ", current->value);
		current = current->next;
	}
  printf("\n");

	extract_words_from_lexer(head);
  extract_words_from_lexer(head);

	printf("\nSecond print:\n");
	current = *head;
	while (current)
	{
		printf("%s ", current->value);
		current = current->next;
	}
  printf("\n");
  return 0;
}