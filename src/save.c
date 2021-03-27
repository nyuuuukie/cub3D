/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 17:05:13 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/27 14:57:18 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	bitmap_header(t_all *all, int fd)
{
	int		lint;
	short	sint;

	write(fd, "BM", 2);
	lint = 14 + 40 + all->map->w * all->map->h * 4;
	write(fd, &lint, sizeof(lint));
	sint = 0;
	write(fd, &sint, sizeof(sint));
	write(fd, &sint, sizeof(sint));
	lint = 14 + 40;
	write(fd, &lint, sizeof(lint));
}

void	bitmap_info_header(t_all *all, int fd)
{
	int		lint;
	short	sint;

	lint = 40;
	write(fd, &lint, sizeof(lint));
	lint = all->map->w;
	write(fd, &lint, sizeof(lint));
	lint = all->map->h;
	write(fd, &lint, sizeof(lint));
	sint = 1;
	write(fd, &sint, sizeof(sint));
	sint = 32;
	write(fd, &sint, sizeof(sint));
	lint = 0;
	write(fd, &lint, sizeof(lint));
	lint = all->map->w * all->map->h * 4;
	write(fd, &lint, sizeof(lint));
	lint = 2795;
	write(fd, &lint, sizeof(lint));
	write(fd, &lint, sizeof(lint));
	lint = 0;
	write(fd, &lint, sizeof(lint));
	write(fd, &lint, sizeof(lint));
}

char	*bitmap_check_exist()
{
	static int index;
	char *filename;
	char *num;
	int fd;

	fd = 1;
	while (fd > 0)
	{
		num = ft_itoa(index++);
		filename = ft_strjoin(num, ".bmp");
		fd = open(filename, O_RDONLY);
		if (fd < 0)
			return (filename);
		free(num);
		free(filename);
		close(fd);
	}
	return (NULL);
}

void	bitmap_to_file(t_all *all)
{
	int		fd;
	int		index;
	char	*filename;

	filename = bitmap_check_exist();
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		throw_engine_error(all, ERR_NO_FILE, filename);
	bitmap_header(all, fd);
	bitmap_info_header(all, fd);
	index = all->map->h;
	while (--index >= 0)
	{
		write(fd, all->img.addr + index * all->map->w * 4, all->map->w * 4);
	}
	close(fd);
}

void make_screenshot(t_all *all)
{
	init_all(all);
	draw_all(all);
	bitmap_to_file(all);
	free_all(all);
}