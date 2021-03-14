/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 17:05:13 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/14 18:51:34 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	header_bmp(t_all *all, int fd)
{
	int		bytes_t;
	short	bytes_d;

	write(fd, "BM", 2);
	bytes_t = 14 + 40 + all->map->w * all->map->h * 4;//размер файла в байтах
	write(fd, &bytes_t, sizeof(bytes_t));
	bytes_d =0;
	write(fd, &bytes_d, sizeof(bytes_d));
	write(fd, &bytes_d, sizeof(bytes_d));
	bytes_t = 14 + 40;//размер хедеров в байтах
	write(fd, &bytes_t, sizeof(bytes_t));
}

void	header_img(t_all *all, int fd)
{
	int		bytes_t;
	short	bytes_d;

	bytes_t = 40;//размер 2-го хедера
	write(fd, &bytes_t, sizeof(bytes_t));
	bytes_t = all->map->w;//ширина изображения
	write(fd, &bytes_t, sizeof(bytes_t));
	bytes_t = all->map->h;//высота изображения
	write(fd, &bytes_t, sizeof(bytes_t));
	bytes_d =1;
	write(fd, &bytes_d, sizeof(bytes_d));
	bytes_d =32;
	write(fd, &bytes_d, sizeof(bytes_d));
	bytes_t = 0;
	write(fd, &bytes_t, sizeof(bytes_t));
	bytes_t = all->map->w * all->map->h * 4;
	write(fd, &bytes_t, sizeof(bytes_t));
	bytes_t = 2795;
	write(fd, &bytes_t, sizeof(bytes_t));
	write(fd, &bytes_t, sizeof(bytes_t));
	bytes_t = 0;
	write(fd, &bytes_t, sizeof(bytes_t));
	write(fd, &bytes_t, sizeof(bytes_t));
}

void	bmp(t_all *all)
{
	int		fd;
	int		index;

	fd = open("screen.bmp", O_RDWR | O_CREAT | O_TRUNC, 00600 | 00060 | 00006);
	header_bmp(all, fd);
	header_img(all, fd);
	index = (all->map->h) * all->map->w * 4;

	while (index >= 0)
	{
		write(fd, all->img.addr + index, all->map->w * 4);
		index -= all->map->w * 4;
	}
	close(fd);
}

void make_screenshot(t_all *all)
{
	all->mlx = mlx_init();
	if (!all->mlx)
		throw_error(ERR_MLX_WIN_FAIL, 0);

	init_screen_size(all);
	init_img(all, &all->img);
	init_coord(all);
	init_textures(all);
	init_shadow_params(all);
	raycasting(all);
	bmp(all);
}