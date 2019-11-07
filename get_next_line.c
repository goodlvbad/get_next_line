/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oearlene <oearlene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 03:37:47 by oearlene          #+#    #+#             */
/*   Updated: 2019/11/07 21:49:51 by oearlene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_gnl	*ft_add_fd(int fd)
{
	t_gnl	*new;

	if (!(new = (t_gnl *)malloc(sizeof(t_gnl))))
		return (NULL);
	new->fd = fd;
	new->buff = ft_strnew(BUFF_SIZE);
	new->next = NULL;
	return (new);
}

char	*ft_check(char *buff, char **line)
{
	char *p;

	p = NULL;
	if (buff)
	{
		if ((p = ft_strrchr(buff, '\n')))
		{
			*p = '\0';
			*line = ft_strdup(buff);
			ft_strcpy(buff, ++p);
		}
		else
		{
			*line = ft_strdup(buff);
			ft_strclr(buff);
		}
	}
	else
		*line = ft_strnew(1);
	return (p);
}

int		ft_get_line(const int fd, char **line, char **buff)
{
	char	read_buff[BUFF_SIZE + 1];
	int		byte_read;
	char	*tmp;
	char	*p_to_n;

	p_to_n = ft_check(*buff, line);
	while (!p_to_n && (byte_read = read(fd, read_buff, BUFF_SIZE)))
	{
		read_buff[byte_read] = '\0';
		if ((p_to_n = ft_strchr(read_buff, '\n')))
		{
			ft_strcpy((*buff), ++p_to_n);
			ft_strclr(--p_to_n);
		}
		tmp = *line;
		if (!(*line = ft_strjoin(*line, read_buff)) || buff < 0)
			return (-1);
		ft_strdel(&tmp);
	}
	return ((ft_strlen(*line) || byte_read) ? 1 : 0);
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
	return (ft_get_line(pointer->fd, line, &pointer->buff));
}
