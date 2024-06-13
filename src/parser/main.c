#include "../../includes/parser.h"

int main()
{
  t_lexer node1 = { "ls", 0, NULL, NULL };
	t_lexer node2 = { "-l", 0, NULL, NULL };
	t_lexer node3 = { "|", PIPE, NULL, NULL };
	t_lexer node4 = { "echo", 0, NULL, NULL };
	t_lexer node5 = { "hola", 0, NULL, NULL };
	t_lexer node6 = { ">", GREAT, NULL, NULL };
	t_lexer node7 = { "file1", 0, NULL, NULL };

	// Enlazar los nodos
	node1.next = &node2;
	node2.prev = &node1;
	node2.next = &node3;
	node3.prev = &node2;
	node3.next = &node4;
	node4.prev = &node3;
	node4.next = &node5;
	node5.prev = &node4;
	node5.next = &node6;
	node6.prev = &node5;
	node6.next = &node7;
	node7.prev = &node6;

	// Imprimir la lista para verificar
	t_lexer *current = &node1;
	printf("%i\n", count_words_until_pipe(&current));

  return 0;
}