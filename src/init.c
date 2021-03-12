/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:48:07 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/12 15:01:32 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_window(t_all *all)
{
	all->mlx = mlx_init();
	init_screen_size(all);
	all->win = mlx_new_window(all->mlx, all->map->w, all->map->h, "cub3D");
	if (!all->mlx || !all->win)
		throw_error(ERR_MLX_FAIL, 0);
}

void	init_img(t_all *all, t_img *img)
{
	img->img = mlx_new_image(all->mlx, all->map->w, all->map->h);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->len, &img->end);
	if (!img->img || !img->addr)
		throw_error(ERR_MLX_FAIL, 0);
}

void	init_texture(void *mlx, char *path, t_texture *t)
{
	t_img *img;

	img = &t->img; 
	img->img = mlx_xpm_file_to_image(mlx, path, &t->w, &t->h);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->len, &img->end);

	if (!img->img || !img->addr)
		throw_error(ERR_MLX_FAIL, 0);
}

void	init_textures(t_all *all)
{
	init_texture(all->mlx, all->map->NO_path, &all->no);
	init_texture(all->mlx, all->map->SO_path, &all->so);
	init_texture(all->mlx, all->map->WE_path, &all->we);
	init_texture(all->mlx, all->map->EA_path, &all->ea);
}

void	init_screen_size(t_all *all)
{
	int current_width;
	int current_height;

	mlx_get_screen_size(&current_width, &current_height);
	if (all->map->h > current_height)
		all->map->h = current_height;
	if (all->map->w > current_width)
		all->map->w = current_width;
}