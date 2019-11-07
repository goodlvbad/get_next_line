/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oearlene <oearlene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 04:09:03 by oearlene          #+#    #+#             */
/*   Updated: 2019/11/07 22:59:05 by oearlene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int     main(int ac, char **ag)
{
    char *line = 0;
    int fd;
    int fd1;

    ac = 0;
    fd = open(ag[1], O_RDONLY);
    fd1 = open(ag[2], O_RDONLY);
	while (get_next_line(fd, &line))
	{
		printf("%s\n", line);
		free(line);
		line = 0;
	}
	printf("%d\n\n", close(fd));
    while (get_next_line(fd1, &line))
	{
		printf("%s\n", line);
		free(line);
		line = 0;
	}
	printf("%d\n\n", close(fd1));
    return (0);
}