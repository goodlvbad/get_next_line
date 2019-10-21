/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oearlene <oearlene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 03:37:47 by oearlene          #+#    #+#             */
/*   Updated: 2019/10/21 05:17:26 by oearlene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *check_overflow(char *over, char **line)
{
    char    *p;

    p = NULL;
    if (over)
    {
        if ((p = ft_strrchr(over, '\n')))
        {
            *p = '\0';
            *line = ft_strdup(over);
            ft_strcpy(over, ++p);
        }
        else
        {
            *line = ft_strdup(over);
            ft_strclr(over);
        }
    }
    else
        *line = ft_strnew(1);
    return (p);
}

int     get_next_line(int fd, char **line)
{
    char            buff[BUFF_SIZE + 1];
    int             byte_read;
    char            *p;
    static char     *over;
    char            *tmp;

    p = check_overflow(over, line);
    while (!p && (byte_read = read(fd, buff, BUFF_SIZE)))
    {
        buff[byte_read] = '\0';
        if ((p = ft_strrchr(buff, '\n')))
        {
            *p = '\0';
            over = ft_strdup(++p);
        }
        tmp = *line;
        *line = ft_strjoin(*line, buff);
        free(tmp);
    }
    return ((byte_read || ft_strlen(over) || ft_strlen(*line)) ? 1 : 0);
}
