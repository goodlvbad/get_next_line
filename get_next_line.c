/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oearlene <oearlene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 03:37:47 by oearlene          #+#    #+#             */
/*   Updated: 2019/10/31 04:43:22 by oearlene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_gnl	*ft_add_fd(int fd)
{
	t_gnl *new;

	if (!(new = (t_gnl *)malloc(sizeof(new))))
		return (NULL);
	new->fd = fd;
	new->content = ft_strnew(BUFF_SIZE);
	new->next = NULL;
	return (new);
}

char	*ft_check(char **p, char *content)
{
	char *s;

	if ((*p = ft_strchr(content, '\n')))
	{
		s = ft_strsub(content, 0, *p - content);
		ft_strcpy(content, ++(*p));
	}
	else
	{
		s = ft_strnew(ft_strlen(content) + 1);
		ft_strcat(s, content);
		ft_strclr(content);
	}
	return (s);
}

int		ft_get_line(int fd, char **line, char **content)
{
	char	buff[BUFF_SIZE + 1];
	int		byte;
	char	*p;
	char	*tmp;

	p = NULL;
	byte = 1;
	*line = ft_check(&p, *content);
	while (!p && (byte = read(fd, buff, BUFF_SIZE)))
	{
		buff[byte] = '\0';
		if ((p = ft_strchr(buff, '\n')))
		{
			ft_strcpy(*content, ++p);
			ft_strclr(--p);
		}
		tmp = *line;
		if (!(*line = ft_strjoin(tmp, buff)) || byte < 0)
			return (-1);
		ft_strdel(&tmp);
	}
	return ((ft_strlen(*line) || ft_strlen(*content) || byte) ? 1 : 0);
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
