/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 07:10:17 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/20 01:06:24 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int   get_next_line(int fd, char **line)
{
	char	*buf;
	int		res;
	int		i;

	i = 0;
	buf = 0;
	if (fd < 0 || read(fd, &buf[i], 0) || !line || !(buf = malloc(1000000)))
		return (-1);
	while ((res = read(fd, &buf[i], 1)) > 0 && buf[i] != '\n')
		i++;
	buf[i] = '\0';
	res != -1 ? *line = buf : free(buf);
	return (res);
}