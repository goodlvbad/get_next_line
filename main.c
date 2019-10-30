/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oearlene <oearlene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 04:09:03 by oearlene          #+#    #+#             */
/*   Updated: 2019/10/30 03:14:39 by oearlene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int     main(void)
{
	char *line;
	int fd1;
	int fd2;
	int i;

	fd1 = open("/Users/oearlene/Desktop/get_next_line/text.txt", O_RDONLY);
	for(i = 0; 3 > i; i++)
	{
		get_next_line(fd1, &line);
		printf("%s\n\n", line);
		free(line);
	}
	fd2 = open("/Users/oearlene/Desktop/get_next_line/test.txt", O_RDONLY);
	for(i = 0; 3 > i; i++)
	{
		get_next_line(fd2, &line);
		printf("%s\n\n", line);
		free(line);
	}
	return (0);
}
