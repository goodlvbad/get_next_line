/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oearlene <oearlene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 05:08:20 by oearlene          #+#    #+#             */
/*   Updated: 2019/11/02 00:32:29 by oearlene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 32

# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"

# include <stdio.h>

/*
** t_read		Struct for reading
** read_buff	Read buffer
** buff			Buffer to keep already reading content from the first '\n'
** tmp			Pointer to temporary buffer used when reallocating line buffer
** byte_read	The read function return value
** p_to_n		The ft_strchr function return value (pointer to '\n')
** t_gnl		Struct for file descriptors
** fd			File descriptor
** read1		Struct for reading in accordance with file descriptor
** next			Next element in chained list
*/

typedef struct		s_read
{
	char			*read_buff;
	char			*buff;
	char			*tmp;
	int				byte_read;
	char			*p_to_n;
}					t_read;

typedef struct		s_gnl
{
	int				fd;
	t_read			read1;
	struct s_gnl	*next;
}					t_gnl;

int					get_next_line(const int fd, char **line);

#endif
