/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oearlene <oearlene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 05:08:20 by oearlene          #+#    #+#             */
/*   Updated: 2019/10/21 05:10:51 by oearlene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#define BUFF_SIZE 35

#include <unistd.h>
#include <fcntl.h>
#include "libft/libft.h"

#include <stdio.h>

int     get_next_line(int fd, char **line);

#endif
