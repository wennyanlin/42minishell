/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:48:09 by rtorrent          #+#    #+#             */
/*   Updated: 2024/10/16 19:12:02 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  <stdio.h>

int main(int argc, char *argv[])
{
	int n = argc;
	printf("# arguments: %d\n", argc);
	while (argc)
		printf("%2d>>%s<<\n", n - argc--, *argv++);
}
