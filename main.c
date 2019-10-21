/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oearlene <oearlene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 04:09:03 by oearlene          #+#    #+#             */
/*   Updated: 2019/10/21 03:37:40 by oearlene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int     main()
{
    char *line;
    int fd;

    fd = open("text.txt", O_RDONLY);
    while (get_next_line(fd, &line))
        printf("%s\n\n", line);
    return (0);
}