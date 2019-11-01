/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oearlene <oearlene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 03:37:47 by oearlene          #+#    #+#             */
/*   Updated: 2019/11/01 04:22:06 by oearlene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
**
** fd			File descriptor
**
** buff			хранит остаток от уже прочитанного (все что после '\n')
** tmp			Pointer to temporary buffer used when reallocating line buffer
** read_buff	Read buffer
**
** byte_read	возвращаемое значение read (то сколько byte прочитали) -> в массиве это будет последний элемент (который мы +1 делали к BUFF_SIZE)
** p_to_n		указатель на '\n' в прочитанном буфере
** next			Next element in chained list
*/

//Отдельно выделили структуру для хранения данных чтения из файла
typedef struct 		s_read
{
	char			*buff;
	char			*tmp;
	char			*tmp1;
	char			*read_buff;
	int				byte_read;
	char 			*p_to_n;
} 					t_read;

//Связали fd с тем, что у нас происходит когда читаем по этому fd;

typedef struct		s_gnl
{
	int				fd;
	t_read			read1;
	struct s_gnl	*next;
}					t_gnl;

t_gnl	*ft_add_fd(int fd)
{
	t_gnl *new;

	if (!(new = (t_gnl *)malloc(sizeof(t_gnl))))
		return (NULL);
	new->fd = fd;

// инициализировали нашу структуру для чтения связанную с конкретным fd

	new->read1.byte_read = 0;
	new->read1.read_buff = ft_strnew(BUFF_SIZE);
	new->read1.p_to_n = NULL;
	new->read1.tmp = NULL;
	new->read1.tmp1 = NULL;
	new->read1.buff = ft_strnew(BUFF_SIZE);

	new->next = NULL;
	return (new);
}

char		*ft_check(t_read p1)
{
	/*
	 * принимает адресс указателя на '\n' и остатка(buff)
	 * ищет в buff '\n'
	 * и записывает в строку (кот вернет) все что до '\n'
	 * если '\n' в buff нет,
	 * то просто записывает все что, есть в buff в новую строку
	 * и очищает buff
	 */

	/*
	 * ft_strrchr возвращает указатель на '\n' первый с конца,
	 * т.е. в строке             | he \n ll \n o wo \n rld \0 |
	 * будет показывать вот сюда |                   ^        |
	 * tmp = buff ( he \n ll \n o wo \n rld \0 ) (buff не трогаем пока)
	 * нужно сохранить все, что до указателя в tmp
	 * пока не дойдем до самой первой \n
	 * | he \n ll \n o wo \n rld \0 |
	 * |     ^                      | <= p1.p_to_n указывает
	 * tmp = "he "
	 * в line надо передать tmp
	 * в buff переписать все, что после \n
	 * очистить tmp
	 * почистить p1.p_to_n
	 */

	char *str;

	p1.tmp = p1.buff;
	if ((p1.p_to_n = ft_strchr(p1.buff, '\n')))
	{
		while ((p1.p_to_n = ft_strrchr(p1.tmp, '\n')))
			p1.tmp = ft_strsub(p1.tmp, 0, (p1.p_to_n - p1.tmp));
		str = ft_strsub(p1.tmp, 0, (p1.p_to_n - p1.tmp));
		ft_strcpy(p1.buff, ++p1.p_to_n);
		ft_strclr(--p1.p_to_n);
	}
	else
	{
		str = ft_strnew(ft_strlen(p1.buff) + 1);
		ft_strcat(str, p1.buff);
		ft_strclr(p1.buff);
	}
	ft_strdel(&p1.tmp);
	return (str);
}

/*
 * t_read p  это инициализация структуры для чтения, чтобы обращаться к полям этой структуры
 * саму структуру мы передали указателем из главной функции
 * тк она связана с fd
*/

int			ft_get_line(const int fd, char **line, t_read p)
{
	/* вызываем функцию, которая будет проверять buff =>
	 * *line = ft_check();
	 * и возвращать указатель на строку, где храниться часть от '\n' до '\n'
	 */

	/* читаем и записываем в line нашу линию из файла */

	*line = ft_check(p);
	while ((p.byte_read = read(fd, p.read_buff, BUFF_SIZE)))
	{
		p.read_buff[p.byte_read] = '\0';  // Hello \n Wor \0

	/*
	 * ft_strrchr возвращает указатель на '\n' первый с конца,
	 * т.е. в строке             | he \n ll \n o wo \n rld \0 |
	 * будет показывать вот сюда |                   ^        |
	 * tmp = read_buff ( he \n ll \n o wo \n rld \0 ) (read_buff не трогаем пока)
	 * нужно сохранить все, что до указателя в tmp
	 * пока не дойдем до самой первой \n
	 * | he \n ll \n o wo \n rld \0 |
	 * |     ^                      | <= p1.p_to_n указывает
	 * tmp = "he "
	 * в line надо передать tmp
	 * в buff переписать все, что после \n
	 * очистить tmp
	 * почистить p1.p_to_n
	 */
		p.tmp1 = p.read_buff;
		if ((p.p_to_n = ft_strrchr(p.tmp1, '\n')))
		{
			p.tmp = p.p_to_n;
			while ((p.tmp = ft_strrchr(p.read_buff, '\n')))
				p.read_buff = ft_strsub(p.read_buff, 0, (p.read_buff - p.tmp));
			p.buff = ft_strjoin(++p.tmp, ++p.p_to_n);
			ft_strdel(&p.p_to_n);
			ft_strdel(&p.tmp);
		}
		p.tmp = *line;
		if (!(*line = ft_strjoin(*line, p.tmp1)))
			return (-1);
		ft_strdel(&p.tmp);
	}
	return ((ft_strlen(*line) || p.byte_read) ? 1 : 0);
}

int		get_next_line(const int fd, char **line)
{
	static t_gnl *head;
	t_gnl *pointer;

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
//	return ( вызываем функцию ft_get_line() );
	return (ft_get_line(pointer->fd, line, pointer->read1));
}
