/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oearlene <oearlene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 03:37:47 by oearlene          #+#    #+#             */
/*   Updated: 2019/11/02 00:15:44 by oearlene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_gnl	*ft_add_fd(int fd)
{
	t_gnl	*new;

	if (!(new = (t_gnl *)malloc(sizeof(t_gnl))))
		return (NULL);
	new->fd = fd;
	new->read1.byte_read = 0;
	new->read1.read_buff = ft_strnew(BUFF_SIZE);
	new->read1.p_to_n = NULL;
	new->read1.tmp = NULL;
	new->read1.buff = ft_strnew(BUFF_SIZE);
	new->next = NULL;
	return (new);
}

char	*ft_check(t_read p1)
{
	if ((p1.p_to_n = ft_strchr(p1.buff, '\n')))
	{
		p1.tmp = ft_strsub(p1.buff, 0, p1.p_to_n - p1.buff);
		ft_strcpy(p1.buff, ++p1.p_to_n);
	}
	else
	{
		p1.tmp = ft_strnew(ft_strlen(p1.buff) + 1);
		ft_strcat(p1.tmp, p1.buff);
		ft_strclr(p1.buff);
	}
	return (p1.tmp);
}

int		ft_get_line(const int fd, char **line, t_read p)
{
	*line = ft_check(p);
	while (p.p_to_n == NULL && (p.byte_read = read(fd, p.read_buff, BUFF_SIZE)))
	{
		p.read_buff[p.byte_read] = '\0';
		if ((p.p_to_n = ft_strchr(p.read_buff, '\n')))
		{
			ft_strcpy(p.buff, ++p.p_to_n);
			ft_strclr(--p.p_to_n);
		}
		p.tmp = *line;
		if (!(*line = ft_strjoin(*line, p.read_buff)))
			return (-1);
		ft_strdel(&p.tmp);
	}
	return ((ft_strlen(*line) || p.byte_read) ? 1 : 0);
}

int		get_next_line(const int fd, char **line)
{
	static t_gnl	*head;
	t_gnl			*pointer;

	if (fd < 0 || line == NULL)
		return (-1);
	if (head == NULL)
		head = ft_add_fd(fd);
	pointer = head;
	while (pointer->fd != fd)
	{
		if (pointer->next == NULL)
			pointer->next = ft_add_fd(fd);
		pointer = pointer->next;
	}
	return (ft_get_line(pointer->fd, line, pointer->read1));
}
