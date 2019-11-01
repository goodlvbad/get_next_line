/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oearlene <oearlene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 04:09:03 by oearlene          #+#    #+#             */
/*   Updated: 2019/11/01 22:53:05 by oearlene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int     main(void)
{
    char *line;
    int fd;
    int fd1;

    fd = open("/Users/oearlene/Desktop/get_next_line-c37917e920c9a00c4dad8e8951827d130f056770/test.txt", O_RDONLY);
    fd1 = open("/Users/oearlene/Desktop/get_next_line-c37917e920c9a00c4dad8e8951827d130f056770/text.txt", O_RDONLY);
    get_next_line(fd, &line);
    printf("%s\n\n", line);
    free(line);
	get_next_line(fd1, &line);
	printf("%s\n\n", line);
	free(line);
	get_next_line(fd, &line);
	printf("%s\n\n", line);
	free(line);
	get_next_line(fd1, &line);
	printf("%s\n\n", line);
	free(line);
	get_next_line(fd, &line);
	printf("%s\n\n", line);
	free(line);
	get_next_line(fd1, &line);
	printf("%s\n\n", line);
	free(line);
	get_next_line(fd, &line);
	printf("%s\n\n", line);
	free(line);
	get_next_line(fd1, &line);
	printf("%s\n\n", line);
	free(line);
    close(fd);
    close(fd1);

    return (0);
}