/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oearlene <oearlene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 03:37:47 by oearlene          #+#    #+#             */
/*   Updated: 2019/10/30 22:02:34 by oearlene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_check_overflow(char *content, char **line)
{
	char *p;

	p = NULL;
	if (content)
	{
		if ((p = ft_strrchr(content, '\n')))
		{
			*p = '\0';
			*line = ft_strdup(content);
			ft_strcpy(content, ++p);
			free(content);
		}
		else
		{
			*line = ft_strdup(content);
			free(content);
		}
	}
	else
		*line = ft_strnew(1);
	return (p);
}

int		ft_get_line(int fd, char **line, char **content)
{
	char	buff[BUFF_SIZE + 1];
	int		byte_read;
	char	*p;
	char	*tmp;

	p = ft_check_overflow(*content, line);
	while (!p && (byte_read = read(fd, buff, BUFF_SIZE)))
	{
		buff[byte_read] = '\0';
		if ((p = ft_strrchr(buff, '\n')))
		{
			*p = '\0';
			*content = ft_strdup(++p);
		}
		tmp = *line;
		if (!(*line = ft_strjoin(*line, buff)) || buff < 0)
			return (-1);
		free(tmp);
	}
	return ((byte_read || ft_strlen(*line)) ? 1 : 0);
}

t_gnl	*ft_add_fd(int fd)
{
	t_gnl *new;

	new = (t_gnl *)malloc(sizeof(t_gnl));
	new->fd = fd;
	new->content = NULL;
	new->next = NULL;
	return (new);
}

int		get_next_line(int fd, char **line)
{
	static t_gnl	*head;
	t_gnl			*tmp;

	if (fd < 0 || line == NULL)
		return (-1);
	if (head == NULL)
		head = ft_add_fd(fd);
	tmp = head;
	while (tmp->fd != fd)
	{
		if (tmp->next == NULL)
			tmp->next = ft_add_fd(fd);
		tmp = tmp->next;
	}
	return (ft_get_line(tmp->fd, line, &tmp->content));
}
