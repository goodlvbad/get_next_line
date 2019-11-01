/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oearlene <oearlene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 04:09:03 by oearlene          #+#    #+#             */
/*   Updated: 2019/11/01 02:21:11 by oearlene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int     main(void)
{
    char *line;
    int fd;
  //  int fd1;

    fd = open("/Users/oearlene/Desktop/get_next_line-c37917e920c9a00c4dad8e8951827d130f056770/test.txt", O_RDONLY);
    get_next_line(fd, &line);
    printf("%s\n\n", line);
    close(fd);

    return (0);
}